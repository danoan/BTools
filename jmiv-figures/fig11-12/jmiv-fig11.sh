#!/usr/bin/env bash

SCRIPT_FOLDER=$( cd $(dirname ${BASH_SOURCE[0]}) >/dev/null 2>&1 && pwd)
DATA_FOLDER=${SCRIPT_FOLDER}/data
EXT_FOLDER=${SCRIPT_FOLDER}/ext
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p ${OUTPUT_FOLDER}/schoenemann
mkdir -p ${OUTPUT_FOLDER}/bc

replace_line()
{
    FILE=$1
    LINE_NUMBER=$2
    NEW_TEXT="$3"

    T1=$(($LINE_NUMBER - 1))
    T2=$(($LINE_NUMBER + 1))

    head $FILE -n$T1 > .temp.part1
    tail $FILE -n+$T2 > .temp.part2

    echo $NEW_TEXT >> .temp.part1
    cat .temp.part1 .temp.part2 > $1

    rm .temp.part1 .temp.part2
}

find_line_number_first_ocurrence()
{
    TEXT_TO_FIND="$1"
    FILE=$2

    echo $(grep "${TEXT_TO_FIND}"  $FILE -n | head -n1 | cut -d: -f1)
}

configure_schoenemann()
{
    CBC_BUILD=${EXT_FOLDER}/cbc-build
    if [ ! -d ${EXT_FOLDER} ]
    then
        cd ${EXT_FOLDER}
        git clone --branch=stable/2.9 https://github.com/coin-or/Cbc Cbc-2.9
        cd Cbc-2.9
        git clone --branch=stable/0.8 https://github.com/coin-or-tools/BuildTools/
        ./BuildTools/get.dependencies fetch
        ./configure --prefix=${CBC_BUILD}
        make install
        cd ${SCRIPT_FOLDER}
    fi


    LINE=$(find_line_number_first_ocurrence "COININCLUDEDIR =" "${EXT_FOLDER}/RegionCurv/Makefile")
    replace_line "${EXT_FOLDER}/RegionCurv/Makefile" ${LINE} "COININCLUDEDIR = ${EXT_FOLDER}/cbc-build/include"

    LINE=$(find_line_number_first_ocurrence "COINLIBDIR =" "${EXT_FOLDER}/RegionCurv/Makefile")
    replace_line "${EXT_FOLDER}/RegionCurv/Makefile" ${LINE} "COINLIBDIR = ${EXT_FOLDER}/cbc-build/lib"

    cd ${EXT_FOLDER}/RegionCurv/common
    make
    cd ..
    make

}

init()
{
    tar -xvf ${DATA_FOLDER}/seg-bench.tar.bz2 -C ${DATA_FOLDER}
    tar -xvf ${EXT_FOLDER}/RegionCurv.tar.bz2 -C ${EXT_FOLDER}

    configure_schoenemann
}


IMAGES_FOLDER=${DATA_FOLDER}/seg-bench/images
BC_SEEDS_FOLDER=${DATA_FOLDER}/seg-bench/bc/seeds

PPM_IMAGES_FOLDER=${DATA_FOLDER}/seg-bench/images-ppm
SCHO_SEEDS_FOLDER=${DATA_FOLDER}/seg-bench/schoenemann/seeds
mkdir -p ${PPM_IMAGES_FOLDER}
mkdir -p ${SCHO_SEEDS_FOLDER}

BTOOLS_BIN=$(realpath $1)
GRAB_CUT_APP=${BTOOLS_BIN}/grab-cut
BC_APP=${BTOOLS_BIN}/boundary-correction-app


SCHOENEMANN_APP=${EXT_FOLDER}/RegionCurv/bin/interactiveseg.opt.L64


produce_data()
{
    #Schoenemann needs ppm images format
    cp ${IMAGES_FOLDER}/*.jpg ${PPM_IMAGES_FOLDER}
    mogrify -format ppm ${PPM_IMAGES_FOLDER}/*.jpg
    rm ${PPM_IMAGES_FOLDER}/*.jpg

    cp -r ${BC_SEEDS_FOLDER}/* ${SCHO_SEEDS_FOLDER}

    #Schoenemann interprets seeds in the opposite way as boundary-correction
    find ${SCHO_SEEDS_FOLDER} -name *.pgm | xargs -I{} convert {} -negate {}


    for imgName in $(ls ${BC_SEEDS_FOLDER})
    do
        echo "Creating BC gc-object for ${imgName}"
        $GRAB_CUT_APP ${IMAGES_FOLDER}/${imgName}.jpg \
        ${BC_SEEDS_FOLDER}/${imgName}/mask-fg-0.pgm \
        ${BC_SEEDS_FOLDER}/${imgName}/mask-bg-0.pgm \
        ${BC_SEEDS_FOLDER}/${imgName}/gc-object.xml \
        -u ${BC_SEEDS_FOLDER}/${imgName}/mask-pbfg-0.pgm
    done

    for imgName in $(ls ${SCHO_SEEDS_FOLDER})
    do
        echo "Creating SCHO gc-object for ${imgName}"
        $GRAB_CUT_APP ${IMAGES_FOLDER}/${imgName}.jpg \
        ${SCHO_SEEDS_FOLDER}/${imgName}/mask-fg-0.pgm \
        ${SCHO_SEEDS_FOLDER}/${imgName}/mask-bg-0.pgm \
        ${SCHO_SEEDS_FOLDER}/${imgName}/gc-object.xml \
        -u ${SCHO_SEEDS_FOLDER}/${imgName}/mask-pbfg-0.pgm
    done

}

produce_output()
{
    i=1
    for imgName in $(ls ${BC_SEEDS_FOLDER})
    do
        echo "Boundary correction of image ${BC_SEEDS_FOLDER}/${imgName}"
        $BC_APP "${BC_SEEDS_FOLDER}/${imgName}/gc-object.xml" -i10 -r5 -d5 -q1.0 -t 3.0 -g 0.1 -v \
        -o "${OUTPUT_FOLDER}/bc/${imgName}"&

        if [ $i = "4" ]
        then
            wait
            i=0
        fi
        i=$[$i+1]
    done

    wait

    for imgName in $(ls ${SCHO_SEEDS_FOLDER})
    do
        echo "Schoenemann segmentation of image ${imgName}"
        CUR_OUTPUT_FOLDER=${OUTPUT_FOLDER}/schoenemann/${imgName}
        mkdir -p ${CUR_OUTPUT_FOLDER}

        $SCHOENEMANN_APP -i "${PPM_IMAGES_FOLDER}/${imgName}.ppm" -lambda 0.1 -gamma 1.0 -curv-power 2 \
		-fg-mask "${SCHO_SEEDS_FOLDER}/$imgName/mask-fg-0.pgm" \
		-bg-mask "${SCHO_SEEDS_FOLDER}/$imgName/mask-bg-0.pgm" \
	    -o "${CUR_OUTPUT_FOLDER}/${imgName}.pgm" \
		-no-trws-reuse > ${CUR_OUTPUT_FOLDER}/log-schoenemann.txt
    done

}

init
produce_data
produce_output