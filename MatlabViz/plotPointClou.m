%function plotPointCloud( )
% 載入點雲文件，文件格式如下：
% x y z r g b
% 例如：
% -1.36156 -1.05557 1.21616 255 255 255 

load('C:\pointCloud.txt');  % 實際運行時，替換為真實路徑
clf
figure(1)
h = plot3(pointCloud(:,1),pointCloud(:,2), pointCloud(:,3),'ro');
grid on
xlabel('x')
ylabel('y')
zlabel('z')

hold on

% Plot z axis
z_1 = [0 0];
z_2 = [0 0];
z_3 = [0 6];
plot3(z_1,z_2,z_3, 'LineWidth', 5)
text(0,0,6.7, 'Z', 'FontSize', 15 )

% Plot y axis
y_1 = [0 0];
y_2 = [0 6];
y_3 = [0 0];
plot3(y_1,y_2,y_3, 'LineWidth', 5)
text(0,6.7,0, 'Y', 'FontSize', 15 )

% Plot x axis
x_1 = [0 6];
x_2 = [0 0];
x_3 = [0 0];
plot3(x_1,x_2,x_3, 'LineWidth', 5)
text(6.7,0,0, 'X', 'FontSize', 15 )
