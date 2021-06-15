% Blasius boundary layer solver:
% ODE: f'''+ 0.5*f*f''=0,
% BCs: f(0)=0, f'(0)=0, f(infinity)=1.

% Solved using ODE boundary value problem solver in MATLAB 'bvp4c'
% Need to convert higher order ODEs to system of 1st order ODEs:
% f(1)=f, f(2)=f', f(3)=f''.

% More information of bvp4c solver:  mathworks.com/help/matlab/ref/bvp4c.html

solver = 'bvp4c';
bvpsolver = fcnchk(solver);

infinity = 10; % The position of "infinity" should be large enough such that the solution doesn't change.

xmesh=linspace(0,infinity,1000); % The 1D mesh/grid

initguess = [1 0 0]; %initial guess for [f(1) f(2) f(3)] = [f f' f''];
%Solution can depend on initial guess (particuarly for nonlinear problems)!
solninit = bvpinit(xmesh, initguess); %setting up initialization (mesh+guess)
sol = bvpsolver(@fsode,@fsbc,solninit); %solve ode with bcs

eta=sol.x; %eta solution values
f=sol.y; %f solution values
fp=sol.yp; %derivatives of f solution values
fp1=fp(1,:); %f' solution values

figure
plot(eta,fp1); %plot f' vs eta
axis([0 7 0 1.1]); %set axis limits
xlabel('\eta = y(U/\nu x)^{1/2}', 'FontSize', 16)
ylabel('f''(\eta) = u/U', 'FontSize', 16)
title('Blasius boundary layer: similarity solution', 'FontSize', 16)

A = [eta; fp1];
fileID = fopen('graph.txt','w');
fprintf(fileID,'%f %f\n',A);
fclose(fileID);

%Helper function defining the 3 1st order ODEs
function dfdeta = fsode(eta,f)
%dfdeta = [f' f'' f''']; Recall that f(1)=f,f(2)=f',f(3)=f''.
dfdeta = [f(2)
    f(3)
    -0.5*f(1)*f(3)];
end

%Helper function defining the 3 boundary conditions
function res=fsbc(f0,finf)
%Note the solver will try to make all entries 0.
%res = [f(0)=0, f'(0)=0, f'(infinity)-1=0];
res= [f0(1)
    f0(2)
    finf(2)-1];
end

