function plot_libviso2( flag )
% 载入相机累积姿态矩阵数据
if ( strcmp( flag, 'offline' ) )
    load('G:\0000000000000000000000\offline_odom_xzy.txt')
else
    load('G:\0000000000000000000000\odom_xzy.txt')
    offline_odom_xzy = odom_xzy;
end
clf
% 绘制libviso2原坐标系统（东-地-北）下的三维曲线
figure( 1 )
plot3( offline_odom_xzy( :, 2 ), offline_odom_xzy( :, 3 ), offline_odom_xzy( :, 4 ) );
title( 'libviso2（东-地-北）坐标系' )
xlabel( 'x(m)' )
ylabel( 'y(m)' )
zlabel( 'z(m)' )
grid on

% 绘制东-北-天坐标系统下的三维曲线
figure( 2 )
plot3( offline_odom_xzy( :, 2 ), offline_odom_xzy( :, 4 ), -offline_odom_xzy( :, 3 ) );
title( '东-北-天坐标系' )
xlabel( 'x(m)' )
ylabel( 'y(m)' )
zlabel( 'z(m)' )
grid on

% 由旋转矩阵求四元数
for i = 1 : 373
    R = [ offline_odom_xzy( i, 5 ) offline_odom_xzy( i, 6 ) offline_odom_xzy( i, 7 );
               offline_odom_xzy( i, 8 ) offline_odom_xzy( i, 9 ) offline_odom_xzy( i, 10 );
               offline_odom_xzy( i, 11 ) offline_odom_xzy( i, 12 ) offline_odom_xzy( i, 13 )];
    epsilon_4(i) = 0.5 * ( 1 + R(1,1) + R(2,2) + R(3,3) )^0.5;
    epsilon_1(i) = ( R(3,2) - R(2,3) ) / 4 / epsilon_4(i);
    epsilon_2(i) = ( R(1,3) - R(3,1) ) / 4 / epsilon_4(i);
    epsilon_3(i) = ( R(2,1) - R(1,2) ) / 4 / epsilon_4(i);
    
    x = epsilon_1(i);
    y = epsilon_2(i);
    z = epsilon_3(i);
    w = epsilon_4(i);
    
    % 验证旋转阵和四元数间转化的正确性
    % 结论：正确
    %Rq = [1-2*epsilon_2(i)^2-2*epsilon_3(i)^2, 2*(epsilon_1(i)*epsilon_2(i)-epsilon_3(i)*epsilon_4(i)), 2*(epsilon_1(i)*epsilon_3(i)+epsilon_2(i)*epsilon_4(i));
    %      2*(epsilon_1(i)*epsilon_2(i)+epsilon_3(i)*epsilon_4(i)), 1-2*epsilon_1(i)^2-2*epsilon_3(i)^2, 2*(epsilon_2(i)*epsilon_3(i)-epsilon_1(i)*epsilon_4(i));
    %      2*(epsilon_1(i)*epsilon_3(i)-epsilon_2(i)*epsilon_4(i)), 2*(epsilon_2(i)*epsilon_3(i)+epsilon_1(i)*epsilon_4(i)), 1-2*epsilon_1(i)^2-2*epsilon_2(i)^2];
    
    % 计算欧拉角
    % 参考了以下链接：http://www.cnblogs.com/wqj1212/archive/2010/11/21/1883033.html
    %phi(i) = atan2( 2*(w * z + x * y ), 1 - 2*(z^2 + y^2));
    %theta(i) = asin(2*(w * y - z * x));
    %psi(i) = atan2( 2*(w * x + z * y), 1 - 2*(y^2 + x^2));
    % 经验证，并不一致
    
    % 参考以下链接：http://zhidao.baidu.com/question/573712044
    q = [w x y z];
    [phi(i), theta(i), psi(i)] = quat2angle(q, 'XYZ');
    
    % 反向验证计算
    % R_V = [ cos(theta(i))*cos(psi(i)), -cos(theta(i))*sin(psi(i)), sin(theta(i));
    %        sin(phi(i))*sin(theta(i))*cos(psi(i))+cos(phi(i))*sin(psi(i)), -sin(phi(i))*sin(theta(i))*sin(psi(i))+cos(phi(i))*cos(psi(i)), -sin(phi(i))*cos(theta(i));
    %        -cos(phi(i))*sin(theta(i))*cos(psi(i))+sin(phi(i))*sin(psi(i)), cos(phi(i))*sin(theta(i))*sin(psi(i))+sin(phi(i))*cos(psi(i)), cos(phi(i))*cos(theta(i))];
    % 经验证，结果正确
end

% 绘制欧拉角曲线
figure(3)

subplot( 3,1,1 )
plot(phi)
grid on
title('phi(pitch - around X)')

subplot( 3,1,2 )
plot(theta)
grid on
title('theta(yaw - around Y)')

subplot( 3,1,3 )
plot(psi)
grid on
title('psi(roll - around Z)')

% 参看C++中那个欧拉角计算程序

figure(4)
plot(theta .* (180 / pi),'b--','LineWidth',2)
grid on
title('偏航角曲线')
xlabel('图像帧数')
ylabel('转角(°)')
