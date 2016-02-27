cross_type=$1
compiler=""
if [ "$1" == "x86" ]; then
	compiler="i686"
else
	compiler="x86_64"
fi;

echo "Cross compiling for $1 ($compiler)"
mkdir bin-cross$cross_type -p
cd bin-cross$cross_type
cmake .. -DIS_SFML=0 -DCMAKE_TOOLCHAIN_FILE="../cross/cross$compiler.cmake" -DCURSES_LIBRARY="/usr/$compiler-w64-mingw32/lib/libpdcurses.dll.a"
make -j4
