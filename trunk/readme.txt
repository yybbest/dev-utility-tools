   welcome to dev-utility-tools projects! dev-utility-tools projects support tools set to bring  developer more convenient!

   now only a tool:SetPrjProps. SetPrjProps can batch modify visual projects propertys (only VS2008 VC projects,include MFC project,Win32 project and console project).


                            the usage of SetPrjProps                      

   SetPrjProps is a command line tool, its usage as follow:

   SetPrjProps ini file sloution file

   e.g: SetPrjProps D:\dev-utility-tools\src\bcg_props.ini D:\dev-utility-tools\src\Test.sln 


                           How to compile source code 

   first you can run SetEnv.bat in src folder to set third party libary envirment.
 
   the develop enviroment is Visual studio 2008 + sp, win xp. so you should use Visual studio 2008
to compile source code. but compile source code only use some Win API and STL. so vs2003、vs2005 and vs 2006 is compatible,maybe vc 6.0, but I cannot sure.

                           Catalog descriptions

   readme.txt  ！！  you konw.

   doc  ！！   now is none, to use place some dev documents.

   src  ！！ all code is here, include:
       
         SetPrjProps ！！ code of SetPrjProps tool.

         Mfc3  ！！ mfc test project
         ConsoleTest ！！ console test project
         Win32Test   ！！ win32 project

         bcg_props.ini ！！ project propety ini file
         ModifySln.bat  ！！ a demo to run SetPrjProps tool
         SetEnv.bat     ！！ a bat file to set third party library envirment

         ThirdPartyLib ！！ a folder to place third party lib and inc files.



         I hope you can enjoy it!




   

     

    