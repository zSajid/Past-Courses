% % %Initialization
% % clc, close all
% % clear
% % 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % disp('Reading in Training Data...' );
% % [training] = tdfread('training.txt',' ');
% % disp('Read in Complete' );
% % 
% % % training = training.InfoID training.FeatureID training.FeatureVal
% % % training ( data.ID );
% % 
% % disp('Reading in Label Data...' );
% % [label] = tdfread('label_training.txt',' ');
% % disp('Read in Complete' );
% % 
% % %label = label.label 
% % %disp(label.label);
% % 
% % training.label = label.label;
% % FeatureID = training.FeatureID;
% % FeatureVal = training.FeatureVal;
% % InfoID = training.InfoID;
% % Label = training.label;
% % 
% % 
% %  labelIndex = length(Label);
% %  trainingIndex = length(InfoID);
% %  total = 0;
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  
% labelIndex = length(Label);
% trainingIndex = length(InfoID);
% total = 0;
% 
%  
%  
%  
% %build pca vars
% %loop 18k
% for i=1:labelIndex
%     %loop 400k
%     total = 0;
%     for j=1:trainingIndex
%         %if value at info id (many 1's) == 
%        if InfoID(j) == i
%            total = total + 1;
%            ObjFeatureIDList(total, i) = FeatureID(j);
%            ObjFeatureValList(total, i) = FeatureVal(j);
%        end
%     end
% %     coeff1 = pca(ObjFeatureValList);
% %     coeff2 = pca(ObjFeatureIDList);
% %     PCAData(i) = coeff1;
%        XY(:, 1) = ObjFeatureIDList(:,i);
%        XY(:, 2) = ObjFeatureValList(:,i);
%        [coeff1, score] = pca(XY);
%        for t=1:1848
%        AllCoef(i, t) = score(t, 1);
%      
%        end
%       
%        disp(i);
% end
%  %coeff1 = pca(ObjFeatureValList(:,1));
% %plot(ObjFeatureIDList(:,1), ObjFeatureValList(:, 1), '.r');
% 
% 
% 
% 
% 
%  
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  
% % 
% % %create label for ever feature, obsolete
% % %loop 18k
% % for i=1:labelIndex
% %     %loop 400k
% %     for j=1:trainingIndex
% %         %if value at info id (many 1's) == 
% %         tmpMaxFeatureIndex = 0;
% %        if InfoID(j) == i
% %            total = total + 1;
% %            NewLabel(total, 1) = Label(i);
% %        end
% %     end
% % end
% 
% % % disp('Building data type...');
% % % 
% % % % % total = 1;
% % % % % %loop 18k
% % % % % for i=1:labelIndex
% % % % %     %loop 400k
% % % % %     offset = 1;
% % % % % 
% % % % %     for j=1:trainingIndex
% % % % %         
% % % % %        %loop over all features per obj
% % % % %        if InfoID(j) == i
% % % % %            FeaturePerObjList(i, FeatureID(total)) = FeatureVal(j);
% % % % %            offset = offset + 1;
% % % % %            total = total + 1;
% % % % %        end
% % % % %     end
% % % % % end
% % % 
% % % total = 1;
% % % %loop 18k
% % % for i=1:labelIndex
% % %     %loop 400k
% % %     offset = 1;
% % % 
% % %     for j=1:trainingIndex
% % %         
% % %        %loop over all features per obj
% % %        if InfoID(j) == i
% % %            FeaturePerObjList(i, offset) = FeatureVal(j);
% % %            offset = offset + 1;
% % %            total = total + 1;
% % %        end
% % %     end
% % % end
% % % 
% % % 
% % % 
% % % %add object ID, and label data to object
% % % for i=1:labelIndex
% % %     FeaturePerObjList(i, 26365) = Label(i);
% % %     FeaturePerObjList(i, 26366) = i;
% % % end
% % % 
% % % disp('Data object built!');
% 
% 
% %disp(max(FeatureID));
% % 
% % %loop over objects
% % for objectIndex = 1: labelIndex
% %     finalDataType(objectIndex, 1) = objectIndex;
% %    %loop over features
% %    for featureIndex = 1: max(FeatureID)
% %        
% %    end
% % end
% 
% 
% %view (trainedClassifier1, 'Mode','graph');
% 
% % % % % 
% % % % % predictedLabel = predict(trainedClassifier1, InfoIDCopy); 
% % % % % 
% % % % % errors = 0;
% % % % % for i=1:length(predictedLabel)
% % % % %     if  predictedLabel(i) ~= NewLabel(i)
% % % % %         errors = errors +1;
% % % % %     end
% % % % % end
% % % % % 
% % % % % disp(errors);
% % % % % disp( length(predictedLabel) );
% % % % % disp( (length(predictedLabel) - errors) / length(predictedLabel) );
% % % % % 
% % % % % 
% % % % % numNegatives = 0;
% % % % % currentObjID = 1;
% % % % % %loop over 400k
% % % % % for i=1:length(predictedLabel)
% % % % %     
% % % % %     %reset vars if moved to next obj
% % % % %     if currentObjID ~= InfoID(i)
% % % % %         
% % % % %         if numNegatives <= 1
% % % % %         PredictedSmallLabel (1, currentObjID) = 1;
% % % % %         else
% % % % %         PredictedSmallLabel (1, currentObjID) = -1;
% % % % %         end
% % % % %         
% % % % %         currentObjID = currentObjID + 1;
% % % % %         numNegatives = 0;
% % % % %     end
% % % % %     
% % % % %     %update -1 val based on obj
% % % % %     if predictedLabel(i) == -1
% % % % %         numNegatives = numNegatives +1 ;
% % % % %     end
% % % % %     
% % % % % end
% % % % % 
% % % % % 
% % % % % 
% % % % % errors2 = 0;
% % % % % for i=1:length(PredictedSmallLabel)
% % % % %     if  PredictedSmallLabel(1, i) ~= Label(i)
% % % % %         errors2 = errors2 +1;
% % % % %     end
% % % % % end
% % % % % 
% % % % % disp(errors2);
% % % % % disp( length(PredictedSmallLabel) );
% % % % % disp( (length(PredictedSmallLabel) - errors2) / length(PredictedSmallLabel) );
% % % % % 
% 
% 





%csvwrite('test1',allData)



% code to convert large testing label to small testing label
numNegatives = 0;
numTotal = 0;
currentObjID = 1;
%loop 400k
for i=1:length(PredictedTestLabel) %where new label is the predicted class
    %reset vars if moved to next obj
    if currentObjID ~= InfoIDTestData(i)
        if numNegatives < (numTotal / 2)
        PredictedSmallLabel (currentObjID, 1) = 1;
        else
        PredictedSmallLabel (currentObjID, 1) = -1;
        end
        
        currentObjID = currentObjID + 1;
        numNegatives = 0;
        numTotal = 0;
    end
    %update number of features per object
    numTotal = numTotal + 1;
    %update -1 val based on obj
    if PredictedTestLabel(i) == -1
        numNegatives = numNegatives +1 ;
    end
    
end

%save alst value

if numNegatives < (numTotal / 2)
PredictedSmallLabel (currentObjID, 1) = 1;
else
PredictedSmallLabel (currentObjID, 1) = -1;
end









