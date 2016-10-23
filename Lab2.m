%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Erica Lee & Emily Yeh
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clf;

v = data;

voltage = v(1:3:3993);         % Voltage (mV)
swordfish_angle = v(2:3:3993); % Azimuth angle (degrees, x-y plane)
whale_angle = v(3:3:3993);     % Zenith angle (degrees, z axis)

% distance from sensor to letter in meters
r = 1/206 .* (15615 - sqrt(349449369 - 412000.*voltage)); % Distance

theta = pi.*swordfish_angle./180;
phi = pi.*whale_angle./180;

x = r .* cos(phi) .* cos(theta);
y = r .* cos(phi) .* sin(theta);
z = r .* sin(phi);

scatter3(x, y, z);
xlabel('x');
ylabel('y');
zlabel('z');

%%

voltage = scan2(1:2:206);         % Voltage (mV)
swordfish_angle = scan2(2:2:206); % Azimuth angle (degrees, x-y plane)

r = 1/206 .* (15615 - sqrt(349449369 - 412000.*voltage));






