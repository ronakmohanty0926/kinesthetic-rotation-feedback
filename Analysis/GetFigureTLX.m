%specify columns for Errors
%comment out yLim for Time
function GetFigureTLX(var1, var2,var3, column)
hb = figure;

a = length(var1);
b = length(var2);
c = length(var3);


A = [a,b,c];
A = A';
A = sortrows(A);
rowlen = A(1,1);

positions = [0.5 0.55 0.6];

boxplot([var1(1:rowlen,column), var2(1:rowlen,column), var3(1:rowlen,column)],'positions',positions);
ylim([0 21]);

%set(gca,'Xtick',1:8,'XTickLabel',{'Thin-Convex', 'Thin-Concave', 'Fat-Convex', 'Fat-Concave', 'Flat1', 'Flat2', 'Flat3', 'Flat4'});
%set(gca,'Xtick',[1 1.25 1.5],'','','', ''); 
box off;

col = [190,186,218;
141,211,199;
255,255,179;
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
saveas(hb,'RE_Frustration.emf');
clear hb;