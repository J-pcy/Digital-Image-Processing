feature = [1.04549e+08,2.58991e+06,571488,383101,845340,4.70662e+06,169526,43941.4,32614.1,74420.8,907009,45929.6,13590.6,10745.5,26036.4,548891,34733.9,10875,8876.54,23254.1,1.26133e+06,92011.5,29320.4,25182.7,76906.4;
        8.96688e+07,2.5051e+06,629876,479417,1.22772e+06,4.84849e+06,181576,53112.6,44787.6,120760,1.20882e+06,59135.7,18394.1,16203.3,44571.6,849879,50906.8,16419.8,14742,42843.2,2.05655e+06,152040,51154,46117.3,151543;
        5.89201e+07,2.00612e+06,513215,403694,1.04539e+06,3.14759e+06,147340,45242.7,38327.2,98009.7,883826,46974.7,15411.1,13533.3,35340.3,674157,40739.5,13447,11786.4,33054.2,1.70969e+06,124639,41756.1,36234.1,115220;
        1.21124e+07,1.05525e+06,376568,326909,810328,1.01506e+06,93816.7,34301.5,30487.2,78830.5,346663,32409.2,11724.3,10315.3,27851.1,303839,27782.8,9730.6,8475.46,24556.1,877871,78812.1,26873.5,23776,78924;
        1.30145e+07,1.09332e+06,385867,334176,831676,1.0749e+06,100363,36594.5,32833.1,84518.6,377520,35169,12750.8,11487.3,31108,332654,31218,11138.5,9893.04,28136.2,962282,90749,32078.1,29086.8,92837.4;
        1.72624e+07,1.23877e+06,361194,278488,658565,1.27877e+06,102291,32807.5,27047.5,66104.7,390125,33363.5,11388.5,9618.39,24263.9,313852,28221.3,9712.35,8197.48,22211.5,889382,84796.8,28874.7,24961.9,77352.3;
        1.48033e+08,3.76852e+06,646272,273815,250887,6.63238e+06,296377,58854.7,25794,24441.3,1.41431e+06,77839,16750.9,7605.21,7466.71,675933,41322,9572.48,4615.39,5099.88,674212,45648.7,11396.4,6308.91,10724.9;
        1.48176e+08,4.56622e+06,734837,318324,322455,7.16991e+06,367437,70751.6,32170.8,33025.7,1.4042e+06,89169.1,20140.1,9887.17,10683,635606,46129,11514.8,5994.67,7380.83,610151,49428.9,13695.9,8340.73,16170.6;
        1.37567e+08,4.38535e+06,922020,432215,415842,7.34845e+06,309363,68273.4,34223.9,35656,1.62846e+06,79301.7,18198.1,9376.42,10324.3,723040,42061.9,10337.7,5420.09,6293.85,655242,44777.8,12011.2,6886.13,10779.2;
        2.88421e+07,636226,113885,63494.4,107189,1.54726e+06,56968,11521.4,6505.54,11016.3,372445,18672.5,4320.31,2529.65,4469.22,230459,14337,3677.45,2285.47,4560.57,410421,29129.6,8294.32,5975.38,15554.5;
        2.64847e+07,596706,113768,64974.6,108404,1.55175e+06,54971.1,11353.5,6570.2,11305,376901,17902,4137.76,2505.53,4557.51,235897,13925.3,3638.52,2363.05,4768.56,437643,30596.6,9233.98,6864.39,17229.8;
        2.93037e+07,659377,123117,69752.9,116806,1.45443e+06,60852.9,12761,7400.92,12724,364103,20485.1,4842.79,2939.05,5393.1,243259,16000.6,4151.36,2656.76,5453.15,468896,33465.2,9500.96,6815.69,17500.1];
[COEFF,SCORE,latent,tsquare] = princomp(feature,'econ');
cumsum(latent)./sum(latent);
SCORE