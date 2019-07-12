usage(){ echo "Usage: $0 "
echo "[-r Ball radius (default: 3)]"
echo "[-t Data fidelity weight (default: 3.0) ]"
echo "[-q Squared curvature weight (default:1.0) ]"
echo "[-g Length weight (default:0.1) ]"
echo "[-i Max iterations (default:30) ]"
echo "BTOOLS_BINARIES_FOLDER INPUT_IMAGE_PATH OUTPUT_FOLDER" 1>&2; exit 1;}

r=3
t=3
q=1
g=0.1
i=30
while getopts ":r:t:q:g:i:" o; do
    case "${o}" in
        r)
            r=$OPTARG
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


SCRIPT_FOLDER=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )

BTOOLS_BIN=$(realpath $1)
INPUT_IMAGE=$(realpath $2)
OUTPUT_FOLDER=$(realpath $3)

mkdir -p $3

SEED_SELECTOR_APP=${BTOOLS_BIN}/seed-selector
GRAB_CUT_APP=${BTOOLS_BIN}/grab-cut
BC_APP=${BTOOLS_BIN}/boundary-correction-app


IMAGE_NAME="$(basename $INPUT_IMAGE)"
IMAGE_NAME="${IMAGE_NAME%%.*}"

SP_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}"

if [ ! -f ${SP_OUT}/mask-bg-0.pgm ]
then
    ${SEED_SELECTOR_APP} ${INPUT_IMAGE} ${OUTPUT_FOLDER} -o
    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" \
    "${SP_OUT}/mask-bg-0.pgm" \
    "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    ${BC_APP} ${SP_OUT}/gc-object.xml -r$r -t$t -q$q -g$g -i$i -o ${SP_OUT}/bc -v -s
fi



while :
do
    ${SEED_SELECTOR_APP} ${INPUT_IMAGE} $OUTPUT_FOLDER \
    -u "${SP_OUT}/mask-pbfg-0.pgm" \
    -f "${SP_OUT}/mask-fg-0.pgm" \
    -b "${SP_OUT}/mask-bg-0.pgm" -o

    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    ${BC_APP} ${SP_OUT}/gc-object.xml -r$r -t$t -q$q -g$g -i$i -o ${SP_OUT}/bc -v -s
done

