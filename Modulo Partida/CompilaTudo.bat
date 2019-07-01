@ECHO  OFF
REM  Compila todos os exemplos simples 


del *.err
del *.obj

pushd  .
nmake /FTestePartidaComInstrumentacao.make 
popd

del *.obj
pushd . 
nmake /FTestePartidaSemInstrumentacao.make
del *.obj

popd

copy  *.err  tudo.err

notepad tudo.err