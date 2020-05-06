import numpy as np
import pandas as pd

data = pd.read_csv('http://archive.ics.uci.edu/ml/machine-learning-databases/car/car.data',names=['buying','maint','doors','persons','lug_boot','safety','class'])

data.head()

#Convert any string values to equivalent integer codes
data['class'],class_names = pd.factorize(data['class'])
data['buying'],_ = pd.factorize(data['buying'])
data['maint'],_ = pd.factorize(data['maint'])
data['doors'],_ = pd.factorize(data['doors'])
data['persons'],_ = pd.factorize(data['persons'])
data['lug_boot'],_ = pd.factorize(data['lug_boot'])
data['safety'],_ = pd.factorize(data['safety'])
#data.head()

X = data.iloc[:,:-1]
y = data.iloc[:,-1]

#Split the data into train and split
from sklearn.model_selection import train_test_split
X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.2,random_state=0)

#Fit the Training data to the model to make predictor
from sklearn.tree import DecisionTreeClassifier

gini = DecisionTreeClassifier(criterion='gini',random_state=0,min_samples_leaf=5)
gini.fit(X_train,y_train)

entropy = DecisionTreeClassifier(criterion='entropy',random_state=0,min_samples_leaf=5)
entropy.fit(X_train,y_train)

#Use the Decision tree model to make prediction on the basis of the test data
#Predicting Result using gini Index Classification
y_pred_Gini = gini.predict(X_test)

#Predicting Result using Entropy Index Classification
y_pred_Entropy = entropy.predict(X_test)

#Draw the Confusion Matrix

from sklearn.metrics import confusion_matrix
print('Confusion Matrix GINI Index')
print(confusion_matrix(y_test,y_pred_Gini))
print('Confusion Matrix Entopy ')
print(confusion_matrix(y_test,y_pred_Entropy))

#Output the accuracy

from sklearn.metrics import accuracy_score
print('Accuracy of GINI index : ',accuracy_score(y_test,y_pred_Gini)*100)
print('Accuracy of Entropy : ',accuracy_score(y_test,y_pred_Entropy)*100)

#Classification Report
from sklearn.metrics import classification_report

print('Report of GINI Index : ',classification_report(y_test,y_pred_Gini))
print('Report of Entropy : ',classification_report(y_test,y_pred_Entropy))
