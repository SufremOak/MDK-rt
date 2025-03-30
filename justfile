alias b := build

build:
    

build-libx:
    gcc lib/*.so.c -o build/lib/*.so
    cp -r lib/include/*.h build/include

mdkpm:
    npx tsc
