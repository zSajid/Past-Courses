%USED USED TO CREATE AND ORGANIZE THE DATA, FROM NOW ON JUST IMPORT THE
%DATA, DONT USE CODE BELOW. 
% %convert datetime string to 24 hour time format
% t = datetime(testingsite3.time,'Format','MM-dd''T''HH:mm:ss')
% %counvert time format to double
% dateDouble = datenum(t);
% 
% %turn wind speed to int
% AggInt = int64(testingsite3.AggregatedValue);
% 
% %save to table
% testingsite3.time = dateDouble;
% testingsite3.AggregatedValue = AggInt;
% 
% for i=1:(size(dateDouble)-1)
% testingsite3.siteNumber(i) = 4;
% end
%combine the created sites
%CombinedSites = vertcat(trainingsite1,trainingsite2,trainingsite3, trainingsite4, trainingsite5,trainingsite6);

%view (classLearner, 'Mode', 'graph');

%PREDICT TESTING DATA BASED ON TRAINING DATA CLASSIFICATION
testingData = predict(classLearner, testsite1Matrix); 

total = 0;
%calc MAE
for i=1:size(testingData)
    total = total + abs( (testingData(i, 1) - testing1actual(i, 1)) );
end
bs = size(testingData);
dataSize = bs(1);

MAE = double(( double(1) / double(dataSize)) * double(total));
disp( 'MAE VALUE IS:')
disp (MAE);

disp( 'RMSE VALUE IS:')
RMSE = double( sqrt( ( double(1) / double(dataSize)) * double(( power(double(total), 2)))));
disp (RMSE);















