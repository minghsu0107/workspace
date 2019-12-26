import pandas as pd
from sklearn.metrics import accuracy_score
from sklearn.metrics import cohen_kappa_score

y_test = pd.read_csv('test_label.csv')
y_pred = pd.read_csv('result.csv')

y_test = y_test['label']
y_pred = y_pred['label']

print("Accuracy: {}".format(accuracy_score(y_test, y_pred)))
print("Cohen Kappa Score: {}".format(cohen_kappa_score(y_test, y_pred, weights='quadratic')))


