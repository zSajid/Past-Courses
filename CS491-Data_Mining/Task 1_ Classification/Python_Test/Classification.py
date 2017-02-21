import numpy  #Import to get the arrays, and for them to parse the data from the file
import sklearn  #Import to get the algorithms for classifcation
from sklearn import tree
from sklearn.cross_validation import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from sklearn import svm
from sklearn.linear_model import LogisticRegression
from sklearn import cross_validation


#Holds training data
x = numpy.loadtxt("training.txt", delimiter =" ")

#Holds target data for the classifier to be trained by
y = numpy.loadtxt("label_big.txt", dtype = numpy.str, delimiter = " ")

#Holds the target data for label_big, but in 'T' or 'F'
z = numpy.loadtxt("label_training_character_replacement.txt", dtype = numpy.str, delimiter = " ")

#Holds the test data information
x_test_data = numpy.loadtxt("testing.txt", delimiter = " ")

#This function just creates an arbitrary file with 1's for 400K lines
def CreateTextData():
    file_object_one = open("label_training_Two.txt", 'w')

    for i in range(0,443403):
        file_object_one.write('1\n')

    file_object_one.close()
    #Print out X and Y to make sure the data is accurate
    print(x.astype(numpy.int64))
    print(y.astype(numpy.int64))

#This function just prints out the data from the label_training
def PrintArray():
    for i in range(1,100):
        print(y.astype(numpy.int64))
        print(x)

# This function creates a new file with the 1's and -1's replaced with T/F
def ReplaceLabelTrainingWithCharacters():
    file_object_one = open("label_training_character_replacement.txt", 'w')

    for i in y:
        print(i)
        if(i == '1'):
            file_object_one.write("T\n")
        else:
            file_object_one.write("F\n")
    file_object_one.close()

def trainDecisionTreeClassification():
    clf =  tree.DecisionTreeClassifier(max_depth = 20)
    clf.fit(x, y)
    y_pred = (clf.predict(x))
    print(metrics.accuracy_score(y,y_pred))
    tree.export_graphviz(clf,out_file='tree.dot')
    return clf

def trainKNeighborsClassification():
    knn = KNeighborsClassifier(n_neighbors = 2, weights = 'distance', algorithm = 'auto', p = 1)
    knn.fit(x, y)
    y_pred = knn.predict(x)
    print(metrics.accuracy_score(y,y_pred))
    return knn

def traingSVMClassifier():
    print("svmClassifier called")
    clf = svm.SVC(kernel ='linear', C =0.1)
    clf.fit(x[0:30000], z[0:30000])
    z_pred = clf.predict(x[0:30000])
    print(metrics.accuracy_score( z[0:30000],z_pred))
    return clf

def trainMLPClassifier():
    mlp = MLPClassifier(alpha=1)
    mlp.fit(x,y)
    y_pred = mlp.predict(x)
    print(metrics.accuracy_score(y, y_pred))
    return mlp

def findClassificationMean():

    kfold = cross_validation.KFold(n=len(x), n_folds= 7, random_state=9)

    knn = KNeighborsClassifier(n_neighbors = 5, weights='uniform', algorithm = 'auto', p = 1)
    knn.fit(x, y)
    y_pred = knn.predict(x)

    results = cross_validation.cross_val_score(knn, x, y, cv=kfold, scoring='accuracy')
    print("Accuracy: %.3f (%.3f)") % (results.mean(), results.std())
    return knn

#Write test label out to file
def writeTestPredictionToFile(test_Item, fileNames):
    file_object_test_data = open(fileNames, 'w')

    for i in test_Item:
        file_object_test_data.write(i + "\n")


#This is for calling classifiers on the data passed in, and getting the trained classifier back
#svm_class = traingSVMClassifier()
#knn_class = trainKNeighborsClassification()
#tree_class = trainDecisionTreeClassification()
#mlp_class = trainMLPClassifier()

knn_class = findClassificationMean()

y_pred = knn_class.predict(x)
test_data_prediction = knn_class.predict(x_test_data)
print(metrics.accuracy_score(y,y_pred))

writeTestPredictionToFile(test_data_prediction, "label_test_knn.txt")

#test_data_prediction = tree_class.predict(x_test_data)
#writeTestPredictionToFile(test_data_prediction, "label_test_tree.txt")

#test_data_prediction = mlp_class.predict(x_test_data)
#writeTestPredictionToFile(test_data_prediction, "label_test_mlp.txt")
