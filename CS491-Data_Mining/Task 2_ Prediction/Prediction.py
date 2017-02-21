import numpy
import pandas as pd
from sklearn import cross_validation
from sklearn.linear_model import LinearRegression



FileList = ["Prediction_Training_Data/Snake_Range_West_Sagebrush.txt","Snake_Range_East_Salt_Desert_Shrub.txt",  "Snake_Range_West_Pinyon-Juniper.txt", "Snake_Range_East_Sagebrush.txt",
            "Snake_Range_West_Montane.txt", "Snake_Range_West_Subalpine.txt"]

names = ['Date', 'Average', 'Minimum', 'Maximum']

Data_Frame_Snake_Range_Training =  numpy.loadtxt(FileList[0], dtype = numpy.float,  delimiter = ",")
print(Data_Frame_Snake_Range_Training)



#kfold = cross_validation.KFold(len(X_DF_SRT), n_folds = 10, random_state = 7)
#lr = LinearRegression()
#results = cross_validation.cross_val_score(lr, [1.30669792, 0.78410816, 1.11044736 ], [1.30669792, 0.78410816, 1.11044736 ], cv = kfold, scoring= 'mean_absolute_error')
#print("MSE: %.3f (%.3f)") % (results.mean(), results.std())
