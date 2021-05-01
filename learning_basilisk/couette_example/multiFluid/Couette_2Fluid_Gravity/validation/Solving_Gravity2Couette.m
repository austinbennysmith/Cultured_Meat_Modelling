clear all
rho1 = 1;
rho2 = 0.917;
mu1 = 10;
mu2 = 300;
g = 9.8;
l = 0.8;
syms a1 b1 a2 b2 y
cond1 = (-(rho1*g)/mu1)*l^2+a1*l+b1 == (-(rho2*g)/mu2)*l^2+a2*l+b2;
cond2 = b1 == 0;
cond3 = (-(rho2*g)/mu2)+a2+b2 == 1;
cond4 = mu1*((-(2*rho1*g)/mu1)*y+a1) == mu2*((-(2*rho2*g)/mu2)*y+a2);
conds = [cond1, cond2, cond3, cond4];
S = solve(conds, [a1 b1 a2 b2]);
% Running the above code gives the following:
% a1 = (293058234952252489*y)/217974221964732006400 + 885218852610103719069/435948443929464012800
% a2 = 295072950870034573023/4359484439294640128000 - (293058234952252489*y)/54493555491183001600
% b1 = 0
% b2 = (293058234952252489*y)/54493555491183001600 + 2097500648982578141051/2179742219647320064000
% So I can next plug these expressions into my quadratic analytical
% solutions. I'll use capital letters from now on to avoid confusion with
% the above code.
% Y = linspace(0, 1, 101); % from -0.5 to 0.5
% A1 = (293058234952252489*Y)/217974221964732006400 + 885218852610103719069/435948443929464012800; % shift
% A2 = 295072950870034573023/4359484439294640128000 - (293058234952252489*Y)/54493555491183001600;
% B1 = 0;
% B2 = (293058234952252489*Y)/54493555491183001600 + 2097500648982578141051/2179742219647320064000;
% U1 = (-(rho1*g)/mu1)*Y.^2+A1.*Y+B1;
% U2 = (-(rho2*g)/mu2)*Y.^2+A2.*Y+B2;
% plot(Y, U1)
% hold on 
% plot(Y, U2)

Y = linspace(-0.5, 0.5, 101); % from -0.5 to 0.5
A1 = (293058234952252489*(Y+0.5))/217974221964732006400 + 885218852610103719069/435948443929464012800; % shift
A2 = 295072950870034573023/4359484439294640128000 - (293058234952252489*(Y+0.5))/54493555491183001600;
B1 = 0;
B2 = (293058234952252489*(Y+0.5))/54493555491183001600 + 2097500648982578141051/2179742219647320064000;
U1 = (-(rho1*g)/mu1)*(Y+0.5).^2+A1.*(Y+0.5)+B1;
U2 = (-(rho2*g)/mu2)*(Y+0.5).^2+A2.*(Y+0.5)+B2;
plot(Y, U1, 'o', "Linewidth", 2)
hold on 
plot(Y, U2, 'o', "Linewidth", 2)
xlabel('y', 'Fontsize', 20)
ylabel('x velocity', 'Fontsize', 20)
title('Two-phase couette flow with gravity', 'Fontsize', 30)
legend('Analytical U1 solution', 'Analytical U2 solution')
