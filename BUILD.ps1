if ($ARGS[ 0 ] -eq "clean")
{
    Remove-Item *.o, *.exe
    exit
}
make -f build.mk