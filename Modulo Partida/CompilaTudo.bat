@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TestePartida.exe

del *.obj
nmake /FTestePartida.make 

copy  *.err  tudo.err

notepad tudo.err

popd
