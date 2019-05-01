
PROJECT_FOLDER=$PWD
GRAB_CUT_APP=$1
SEED_SELECTOR_APP=$2

INPUT_IMAGE=$(realpath $3)
OUTPUT_FOLDER=$(realpath $4)

IMAGE_NAME=$(basename $INPUT_IMAGE | grep ".*\." -o | tr -d ".")

echo $IMAGE_NAME
SP_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}"

mkdir $OUTPUT_FOLDER

    ${SEED_SELECTOR_APP} -o ${INPUT_IMAGE} $OUTPUT_FOLDER
    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/cow2.xml" -u "${SP_OUT}/mask-pbfg-0.pgm" -s

while :
do
    ${SEED_SELECTOR_APP} -o ${INPUT_IMAGE} $OUTPUT_FOLDER -u "${SP_OUT}/mask-pbfg-0.pgm" -f "${SP_OUT}/mask-fg-0.pgm" -b "${SP_OUT}/mask-bg-0.pgm"
    ${GRAB_CUT_APP} ${INPUT_IMAGE} "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/gc-object.xml" -u "${SP_OUT}/mask-pbfg-0.pgm" -s
done

rm -rf $OUTPUT_FOLDER
