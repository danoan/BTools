SCRIPT_FOLDER=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )

PROJECT_FOLDER=$(cd $SCRIPT_FOLDER && cd .. && pwd)
BTOOLS_BIN=${PROJECT_FOLDER}/install/bin
INPUT_IMAGE=${PROJECT_FOLDER}/images/coala.jpg

usage(){ echo "Usage: $0 "
echo "[-r Ball radius (default: 5)]"
echo "[-l Levels (default: -2)]"
echo "[-t Data fidelity weight (default: 0.5) ]"
echo "[-q Squared curvature weight (default:1.0) ]"
echo "[-g Length weight (default:0.1) ]"
echo "[-i Max iterations (default:30) ]"
echo "[-B BTOOLS_BINARIES_FOLDER (default:$BTOOLS_BIN) ]"
echo "[-I INPUT_IMAGE_PATH (default:$INPUT_IMAGE) ]"
echo " OUTPUT_FOLDER" 1>&2; exit 1;}

r=5
l=-2
t=0.5
q=1
g=0.1
i=30
while getopts ":r:l:t:q:g:i:" o; do
    case "${o}" in
        r)
            r=$OPTARG
            ;;
        l)
            l=$OPTARG
            ;;
	    t)
	        t=$OPTARG
	        ;;
	    q)
	        q=$OPTARG
	        ;;
	    g)
	        l=$OPTARG
	        ;;
	    i)
	        i=$OPTARG
	        ;;
        :)
            echo "Invalid option: $OPTARG requires an argument" 1>&2
            exit 1;
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND -1))

OUTPUT_FOLDER=$1
mkdir -p $OUTPUT_FOLDER

if [ -z $OUTPUT_FOLDER ]
then
    usage
    exit
fi

SEED_SELECTOR_APP=${BTOOLS_BIN}/seed-selector
GRAB_CUT_APP=${BTOOLS_BIN}/grab-cut
BC_APP=${BTOOLS_BIN}/boundary-correction-app


IMAGE_NAME="$(basename $INPUT_IMAGE)"
IMAGE_NAME="${IMAGE_NAME%%.*}"

SP_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}"
mkdir -p $SP_OUT


echo "Output files in: $SP_OUT"
echo ""

SEED_SELECTOR_OUT=""

if [ ! -f ${SP_OUT}/mask-bg-0.pgm ]
then
    ${SEED_SELECTOR_APP} ${INPUT_IMAGE} ${OUTPUT_FOLDER} -o
    if [ $? -eq 0 ]
    then
        exit
    fi

    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" \
    "${SP_OUT}/mask-bg-0.pgm" \
    "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    ${BC_APP} ${SP_OUT}/gc-object.xml -r$r -l$l -t$t -q$q -g$g -i$i -o ${SP_OUT}/bc -v -s
fi



while :
do
    ${SEED_SELECTOR_APP} ${INPUT_IMAGE} $OUTPUT_FOLDER \
    -u "${SP_OUT}/mask-pbfg-0.pgm" \
    -f "${SP_OUT}/mask-fg-0.pgm" \
    -b "${SP_OUT}/mask-bg-0.pgm" -o

    if [ $? -eq 0 ]
    then
        exit
    fi

    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    ${BC_APP} ${SP_OUT}/gc-object.xml -r$r -l$l -t$t -q$q -g$g -i$i -o ${SP_OUT}/bc -v -s
done

