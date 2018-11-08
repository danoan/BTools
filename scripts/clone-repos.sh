ROOT_DIR=$PWD
INSTALL_PATH=$ROOT_DIR/ext
EXT_PROJECT_DIR=$ROOT_DIR/ext-project

rm $EXT_PROJECT_DIR -r -f
rm $INSTALL_PATH -r -f

#--------------DIPaCUS----------------

DIPACUS_DIR=$EXT_PROJECT_DIR/DIPaCUS
mkdir $DIPACUS_DIR -p
git clone https://github.com/danoan/DIPaCUS $DIPACUS_DIR


#--------------GEOC----------------

GEOC_DIR=$EXT_PROJECT_DIR/geoc
mkdir $GEOC_DIR -p
git clone https://github.com/danoan/GEOC $GEOC_DIR


#--------------SCaBOliC----------------

SCABOLIC_DIR=$EXT_PROJECT_DIR/SCaBOliC
mkdir $SCABOLIC_DIR -p
git clone https://github.com/danoan/SCaBOliC $SCABOLIC_DIR



#--------------BinOCS----------------

BINOCS_DIR=$EXT_PROJECT_DIR/BinOCS
mkdir $BINOCS_DIR -p
git clone https://github.com/danoan/BinOCS $BINOCS_DIR
