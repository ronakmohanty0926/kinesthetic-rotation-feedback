%copy all text files into a single folder
%Input Rotation as '*RotationType*', it is case sensitive hence,
%Global/Local/Elastic within * *
%Input Shape as 'ShapeType', it is case sensitive hence,
%Jay/Shoe/Puzzle/Trapezium within ' '
function [shapefileList, Error, Time, Path] = AnalyzeData (Rotation, Shape)

tempfileList = dir(fullfile(pwd,Rotation));
tempfileList = {tempfileList.name}
fileList = string(tempfileList)
fileList = fileList'
if strcmp(Shape,'Jay')
index = find(contains(fileList,'Jay'))
else if strcmp(Shape,'Puzzle')
index = find(contains(fileList,'Puzzle'))    
else if strcmp(Shape,'Shoe')
index = find(contains(fileList,'Shoe'))
else if strcmp(Shape,'Trapezium')
index = find(contains(fileList,'Trapezium'))
else disp
    end
    end
    end
end

shapefileList = fileList(index);
shapefileList = string(shapefileList);

%fileID = zeros(length(shapefileList),1);
Error = zeros(length(shapefileList),3);
Time = zeros(length(shapefileList),1);
Path = zeros(length(shapefileList),3);
%Sty = zeros(length(shapefileList),3);
%HapSty = zeros(length(shapefileList),3);
%tmp = zeros(length(HapSty),3);
for i = 1:1
     count = 0;
    fileID = fopen(fullfile(pwd,shapefileList(i,1)));
    tline = fgetl(fileID);
    tline = fgets(fileID);
    time = split(tline);
    time = time';
    time = string(time);
    Time(i,1) = time(1,3);   
    for k = 1:3
        tline = fgets(fileID);
        tline = split(tline);
        tline = tline';
        tline = string(tline);
        Error(i,k) = tline(1,2);
    end
     for k = 1:9
        tline = fgets(fileID);
     end          
  
    while ~feof(fileID)
        count = count + 1;
        tline = fgets(fileID);
        tline = split(tline);
        tline = tline';
        StyTmp(count,:) = string(tline(:,5:7)); 
    end
    tmp = zeros(length(StyTmp),3);
    for k = 1:length(tmp)
        tmp(k,1) = StyTmp(k,1);
        tmp(k,2) = StyTmp(k,2);
        tmp(k,3) = StyTmp(k,3);
    end
%     tmp1 = zeros(length(tmp)-1,3);
%     for k = 1:length(tmp1)
%         tmp1(k,1) = tmp(k+1,1)-tmp(k,1);
%         tmp1(k,2) = tmp(k+1,2)-tmp(k,2);
%         tmp1(k,3) = tmp(k+1,3)-tmp(k,3);
%     end
%      tmp2 = zeros(length(tmp1),1);
%     for k = 1:length(tmp2)
%         tmp2(k,1) = sqrt((tmp1(k,1)*tmp1(k,1))+(tmp1(k,2)*tmp1(k,2))+(tmp1(k,3)*tmp1(k,3))); 
%     end
%     Path(i,1) = sum(tmp2);
       
    fclose('all');
    clear StyTmp;
    
end


% temp = zeros(length(Time),1);
%      Time = sortrows(Time);
%      for m = 1:length(Time)
%           temp(m,1) = Time(m,1);
%      end
%       %disp(temp);
%       for n = 2:length(Time)
%           Time(n,1) = temp(n,1) - temp(n-1,1);
%            %disp(Time);
%       end
    
end