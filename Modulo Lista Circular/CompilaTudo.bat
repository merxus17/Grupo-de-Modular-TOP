@ECHO  OFF
REM  Compila todos os exemplos simples 


del *.err
del *.obj

pushd  .
nmake /FTesteListaCircular.make 
popd

del *.obj
pushd . 
nmake /FTesteListaCircularDebug.make
del *.obj

popd

copy  *.err  tudo.err

notepad tudo.err

