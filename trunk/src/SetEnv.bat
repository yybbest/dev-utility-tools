@echo off

ver | find "4.0." > NUL &&  goto win_xp    
ver | find "4.10." > NUL &&  goto win_xp   
ver | find "4.90." > NUL &&  goto win_xp   
ver | find "3.51." > NUL &&  goto win_xp   
ver | find "5.0." > NUL &&  goto win_xp    
ver | find "5.1." > NUL &&  goto win_xp    
ver | find "5.2." > NUL &&  goto win_xp    
ver | find "6.0." > NUL &&  goto win7   
ver | find "6.1." > NUL &&  goto win7    
ver | find "6.2." > NUL &&  goto win7    

:win_xp 
rem set environment THIRD_PARTY
wmic ENVIRONMENT where "name='THIRD_PARTY'" delete
wmic ENVIRONMENT create name="THIRD_PARTY",username="<system>",VariableValue="%~dp0ThirdPartyLib"
echo %THIRD_PARTY%


goto end 

:win7
@setx THIRD_PARTY "%~dp0ThirdPartyLib"


goto end

:end
pause