echo "Getting and installing of GRPC stuff."
TARGET_DIR=$1
echo "Target directory: $TARGET_DIR"
INITIAL_DIR=$(pwd)
echo "Current directory: $INITIAL_DIR"
CORES_NUMBER=$(getconf _NPROCESSORS_ONLN)
echo "Number of cores: $CORES_NUMBER"
# ==============================================

echo "Preparing target directory..."
rm -rf $TARGET_DIR && mkdir -p $TARGET_DIR
# ==============================================

echo "Getting GRPC sources..."

GRPS_REPOSITORY_DIR=$TARGET_DIR/Temp
mkdir -p $GRPS_REPOSITORY_DIR

git clone --recurse-submodules -b v1.58.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc $GRPS_REPOSITORY_DIR
# ==============================================

echo "Building GRPC..."

cd $GRPS_REPOSITORY_DIR
mkdir -p cmake/build
cd $GRPS_REPOSITORY_DIR/cmake/build

if [ "$(uname)" == "Darwin" ]; then
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ../..   
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ../..
else
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ../.. -A Win32
fi

cmake --build . --config Release -j$CORES_NUMBER
# ==============================================

echo "Installing GRPC..."

cmake --install . --prefix $TARGET_DIR
# ==============================================

echo "Cleaning..."
rm -rf $GRPS_REPOSITORY_DIR

cd $INITIAL_DIR

echo "Done."
