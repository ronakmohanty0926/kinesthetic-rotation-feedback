%specify columns for Errors
%comment out yLim for Time
function GetFigureMDA(var1, var2,var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, column)
hb = figure;

a = length(var1);
b = length(var2);
c = length(var3);
d = length(var4);
e = length(var5);
f = length(var6);
g = length(var7);
h = length(var8);
i = length(var9);
j = length(var10);
k = length(var11);
l = length(var12);

A = [a,b,c,d,e,f,g,h];
A = A';
A = sortrows(A);
rowlen = A(1,1);

positions = [1 1.01 1.02 1.04 1.05 1.06 1.08 1.09 1.1 1.12 1.13 1.14];

boxplot([var1(1:rowlen,column), var2(1:rowlen,column), var3(1:rowlen,column), var4(1:rowlen,column), var5(1:rowlen,column), var6(1:rowlen,column), var7(1:rowlen,column), var8(1:rowlen,column), var9(1:rowlen,column), var10(1:rowlen,column), var11(1:rowlen,column), var12(1:rowlen,column)],'positions',positions);
ylim([0 10000]);

%set(gca,'Xtick',1:8,'XTickLabel',{'Thin-Convex', 'Thin-Concave', 'Fat-Convex', 'Fat-Concave', 'Flat1', 'Flat2', 'Flat3', 'Flat4'});
%set(gca,'Xtick',[1 1.25 1.5],'','','', ''); 
box off;

col = [190,186,218;
141,211,199;
255,255,179;
190,186,218;
141,211,199;
255,255,179;
190,186,218;
141,211,199;
255,255,179;
190,186,218;
141,211,199;
255,255,179;
% 190,186,218;
%34,94,168;
];

col = col./255;
h = findobj(gca,'Tag','Box');
 for j=1:length(h)
    patch(get(h(j),'XData'),get(h(j),'YData'),col(j,:),'FaceAlpha',1.0);
 end
h = findobj(gca,'Tag','Median');
for j=1:length(h)
    line(get(h(j),'XData'),get(h(j),'YData'),'LineWidth',1.5,'Color','k');
end
h=findobj(gca,'Tag','Outliers');
set(h,'Marker','o');
set(h,'MarkerFaceColor',[0.75 0.75 0.75]);
set(h,'MarkerEdgeColor','k');

set(findobj(gcf,'LineStyle','--'),'LineStyle','-');
set(gcf,'renderer','painter');
saveas(hb,'RE_Path_Overall.emf');
clear hb;