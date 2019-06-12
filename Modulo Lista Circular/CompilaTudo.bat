@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteListaCircular.exe

del *.obj
nmake /FTesteListaCircular.make 

copy  *.err  tudo.err

notepad tudo.err

popd
