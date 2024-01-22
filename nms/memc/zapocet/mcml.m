%% help
% executes one MCML cycle, i.e. shoots input number of photon packets and follows
% their trajectory until dead state reached

%% execute one cycle
function [output] = mcml(input, photon_packet, layer)
    % save input photon_packet value for new launch on previous packet's death
    photon_packet_temp = photon_packet;
    
    % array sizes for saving output
    N_z = input(1).grid_range;
    N_r = input(2).grid_range;
    N_alpha = input(3).grid_range;
    N_l = input.num_of_layers;
    
    % refraction indices init, in fig. 3 only medium and turbid layer used
    n_medium = input(1).refr_ind_medium;
    n_clearLayer = input(1).refr_ind_clearLayer;
    n_turbidLayer = layer(1).refr_ind;
    refr_indices = [n_medium, n_clearLayer, n_turbidLayer];
    
    %output structure def and init acc. to ps. 11-12
    output = struct('Rsp', 0, 'Rd_r_alpha', zeros(N_r, N_alpha), 'Rd_r', zeros(N_r+1),...
        'Rd_alpha', zeros(N_alpha), 'Rd', 0, 'A_r_z', zeros(N_r, N_z), 'A_z', zeros(N_z), ...
        'A_l', zeros(N_l+1), 'A', 0, 'Td_r_alpha', zeros(N_r, N_alpha), ...
        'Td_r', zeros(N_r+1), 'Td_alpha', zeros(N_alpha), 'Td', 0, ...
        'Td_diffuse', 0, 'Td_unscattered', 0);
    
    % implementation of algorithm diagram, fig. 2, p. 4
    for i = 1:input(1).num_of_photons
        % launch photon
        if(photon_packet(1).dead == true)
            photon_packet = photon_packet_temp;
            [photon_packet, output] = photonLaunching(photon_packet, refr_indices, input, output);
        end       
        % photon life cycle after launching
        while(1)
            % get random step size 
            if(photon_packet(1).step_size == 0)
                photon_packet = getRandomPhotonStepSize(photon_packet, layer);
            end           
            % is this stepsize large enough for the photon packet to hit
            % the layer boundary?
            [hit, dist_to_bound] = hitBoundary(photon_packet, layer);
            if(hit == true)  
                % implied by the paragraphs below eq. 3.27
                % move the photon towards the boundary
                photon_packet(1).step_size = dist_to_bound;
                photon_packet = photonMoving(photon_packet);
                photon_packet(1).step_size = photon_packet(1).step_size - dist_to_bound ...
                    * (layer(1).absorb_coeff + layer(1).scatter_coeff);
               
                % angle of potential internal reflectance
                [R_alpha, transmission_angle] = calcR_alpha(photon_packet, n_medium, n_turbidLayer);
                
                % approach no. 1 to utilizing R_alpha, eq. 3.31
%                 ksi = genRandomUniformNumber();
%                 if(ksi <= R_alpha)
%                    photon_packet = photonReflection(photon_packet); 
%                 else
%                    [photon_packet, output] = photonTransmission(photon_packet, layer, input, output, R_alpha, transmission_angle);
%                    photon_packet(1).dead = true;                 
%                 end
                
                
                % approach no. 2 to utilizing R_alpha, bottom right p. 9
                % part of photon is tranmitted (exits layer), remaining
                % part is internally reflected. Slower but more precise
                [photon_packet, output] = photonTransmission(photon_packet, layer, input, output, R_alpha);
                photon_packet = photonReflection(photon_packet, R_alpha);
                
                if(photon_packet(1).weight == 0)
                    photon_packet(1).dead = true;
                end
            else    
                photon_packet = photonMoving(photon_packet);
                photon_packet(1).step_size = 0;
                photon_packet = photonAbsorption(photon_packet, layer);
                photon_packet = photonScattering(photon_packet, layer);
            end
            if(photon_packet(1).dead == true)
                break;
            % random termination roulette, sec. 3.9, p. 10
            elseif(photon_packet(1).weight < 0.0001)
                [photon_packet, survived] = russianRoulette(photon_packet, input(1).roulette_weight);
                if(survived == false)
                   break;
                end
            end
        end
    end
    output = calcResults(input, layer, output);
end

%% generate random number 
% generate random uniformly distributed from U(0, 1)
function [ksi] = genRandomUniformNumber()
    ksi = rand;
end

%% launch photon
% acc. to p. 5
function [photon_packet, output] = photonLaunching(photon_packet, refr_indices, input, output)
    Rsp = calcSpecularReflectance(input(1).num_of_layers, refr_indices, photon_packet);
    % eq. 3.6
    photon_packet(1).dead = false;
    photon_packet(1).weight = photon_packet(1).weight - Rsp;
    output.Rsp = Rsp;
end

%% calculate specular reflectance for launch
% acc. to p. 5
function [Rsp] = calcSpecularReflectance(num_of_layers, refr_indices, photon_packet)
    % layer refraction indices for clearer orientation in eqs. 3.3-3.5
    n_medium = refr_indices(1);
    n_clearLayer = refr_indices(2);
    n_turbidLayer = refr_indices(3);
    
    % without clear intermediary layer, eq. 3.2
    if(num_of_layers == 2)
        Rsp = (n_medium - n_turbidLayer)^2 / (n_medium + n_turbidLayer)^2;
        photon_packet(1).layer = 1;
    % with clear medium layer included, eqs. 3.3, 3.4, 3.5
    elseif(num_of_layers == 3)
        r1 = (n_medium - n_clearLayer)^2 / (n_medium + n_clearLayer)^2;
        r2 = (n_turbidLayer - n_clearLayer)^2 / (n_clearLayer + n_turbidLayer)^2;
        Rsp = r1 + (r2*(1-r1)^2)/(1 - r1*r2);
        photon_packet(1).layer = 2;
    else
        Rsp = 0;
    end
end

%% calculate random photon step size
% acc. to p. 6
function [photon_packet] = getRandomPhotonStepSize(photon_packet, layer)
    mu_a = layer(1).absorb_coeff;
    mu_s = layer(1).scatter_coeff;
    % step size init, eq. 3.13
    if (photon_packet(1).step_size == 0)
        ksi = genRandomUniformNumber();
        photon_packet(1).step_size = -log(ksi) / (mu_a + mu_s);
    % if step size remains
    % implied by the two paragraphs below eq. 3.27
    else
        photon_packet(1).step_size = photon_packet(1).step_size / (mu_a + mu_s);
    end
end

%% move photon by random step size
% acc. to p. 7, eq. 3.17
function [photon_packet] = photonMoving(photon_packet)
    photon_packet(1).cart_coord = photon_packet(1).cart_coord + ...
        photon_packet(1).dir_cosines * photon_packet(1).step_size;
    photon_packet(2).cart_coord = photon_packet(2).cart_coord + ...
        photon_packet(2).dir_cosines * photon_packet(1).step_size;
    photon_packet(3).cart_coord = photon_packet(3).cart_coord + ...
        photon_packet(3).dir_cosines * photon_packet(1).step_size;
end

%% calculate deflection angle for scattering
% acc. to p. 7, eq. 3.22
function [cos_theta] = calcDeflectionAngle(g)
   ksi = genRandomUniformNumber();
   if(g == 0)
       cos_theta = 2*ksi - 1;
   else
       cos_theta = (1 /(2*g))*(1 + g^2 - ((1 - g^2)/(1 - g + 2*g*ksi))^2); 
   end   
end

%% photon absorption, weight decrease
% acc. to p. 7
function [photon_packet] = photonAbsorption(photon_packet, layer)
    mu_a = layer(1).absorb_coeff;
    mu_s = layer(1).scatter_coeff;
    % eq. 3.18
    weight_diff = (mu_a /(mu_a + mu_s)) * photon_packet(1).weight;
    % eq. 3.20
    photon_packet(1).weight = photon_packet(1).weight - weight_diff;
end

%% calculate scattering direction
% acc. to p. 7
function [photon_packet] = photonScattering(photon_packet, layer)
    % initial directional cosines
    mu_x = photon_packet(1).dir_cosines;
    mu_y = photon_packet(2).dir_cosines;
    mu_z = photon_packet(3).dir_cosines;

    cos_theta = calcDeflectionAngle(layer(1).anisotropy);
    % eq. 3.23
    ksi = genRandomUniformNumber();
    psi = 2*pi*ksi;
    % theta is arccos of eq. 3.22
    theta = acos(cos_theta);
    
    % photon scattering and new direction choosing
    % special scatter situation when photon dir. is close to z-axis, p. 8, eq. 3.25
    if(abs(mu_z) > 0.99999)
        photon_packet(1).dir_cosines = sin(theta) * cos(psi);
        photon_packet(2).dir_cosines = sin(theta) * sin(psi);
        photon_packet(3).dir_cosines = sign(mu_z) * cos(theta);
    % general scatter situation, p. 7, eq. 3.24
    else
        photon_packet(1).dir_cosines = sin(theta) * (mu_x * mu_z * cos(psi) - mu_y * sin(psi)) / ...
            sqrt(1 - mu_z^2) + mu_x * cos(theta);
        photon_packet(2).dir_cosines = sin(theta) * (mu_y * mu_z * cos(psi) + mu_x * sin(psi)) / ...
            sqrt(1 - mu_z^2) + mu_y * cos(theta);
        photon_packet(3).dir_cosines = -sin(theta) * cos(psi) * sqrt(1 - mu_z^2) + mu_z * cos(theta);
    end
    % increase the number of scatters by 1
    photon_packet(1).scatters = photon_packet(1).scatters + 1;
end

%% will the photon hit boundary?
% acc. to p. 8
function [hit, dist_to_bound] = hitBoundary(photon_packet, layer)
    mu_a = layer(1).absorb_coeff;
    mu_s = layer(1).scatter_coeff;
    
    % calculate distance to boundary based on direction of z movement,
    % p. 8, eq. 3.26
    % only z-coord needed as x, y are considered infinite
    if(photon_packet(3).dir_cosines < 0)
        dist_to_bound = (layer(1).z_coord - photon_packet(3).cart_coord) / ...
            photon_packet(3).dir_cosines;
    elseif(photon_packet(3).dir_cosines == 0)
        dist_to_bound = inf;
    elseif(photon_packet(3).dir_cosines > 0)
        dist_to_bound = (layer(2).z_coord - photon_packet(3).cart_coord) /...
            photon_packet(3).dir_cosines;
    end
    
    % decide whether distance traversed is enough to hit the boundary,
    % eq. 3.27
    % ~=0 for infinity case
    if(photon_packet(3).dir_cosines ~= 0 && dist_to_bound * (mu_a + mu_s) <= photon_packet(1).step_size)
        hit = true;
    else
        hit = false;
    end
end

%% calc fresnel reflectance R_alpha
% acc. to p. 8
function [R_alpha, transmission_angle] = calcR_alpha(photon_packet, n_medium, n_turbidLayer)
    % eq. 3.28, alpha_i
    incidence_angle = acos(abs(photon_packet(3).dir_cosines));
    
    % transmission angle calculation, Snell's law
    % implied by eq. 3.29 and definition of asin
    if((n_turbidLayer / n_medium) * sin(incidence_angle) > 1)
        transmission_angle = pi/2;
    elseif((n_turbidLayer / n_medium) * sin(incidence_angle) < -1)
        transmission_angle = -pi/2;
    else
        transmission_angle = asin((n_turbidLayer / n_medium) * sin(incidence_angle));
    end
    
    % implied by eq. 3.30, sin(0) + tan(0) = 0
    if(n_medium == n_turbidLayer)
        R_alpha = 0;
    % paragraph below eq. 3.30
    elseif(n_turbidLayer > n_medium && incidence_angle > asin(n_medium / n_turbidLayer))
        R_alpha = 1;
    % eq. 3.30    
    else
        R_alpha = 1/2 * (((sin(incidence_angle - transmission_angle))^2 / ...
            (sin(incidence_angle + transmission_angle))^2) + ...
            ((tan(incidence_angle - transmission_angle))^2 / ...
            (tan(incidence_angle + transmission_angle))^2));
    end
end

%% photon is internally reflected into the layer
% acc. to p. 9
function [photon_packet] = photonReflection(photon_packet, R_alpha)
    % eq. 3.32
    photon_packet(3).dir_cosines = -photon_packet(3).dir_cosines;
    % approach 2 to transmission/reflection, p. 9 bottom right
    photon_packet(1).weight = photon_packet(1).weight*R_alpha;
end

%% photon is transmitted into the next layer
% photon is transmitted into the next layer be it medium or other type or
% next layer
% however, in fig. 3 there is only 1 turbid layer and a medium, hence every
% transmission constitutes an escape into the medium
function [photon_packet, output] = photonTransmission(photon_packet, layer, input, output, R_alpha)
    x = photon_packet(1).cart_coord;
    y = photon_packet(2).cart_coord;
    delta_alpha = input(3).grid_sep;
    delta_r = input(2).grid_sep;
    N_r = input(2).grid_range;
    
    % converting cartesian coords to polar/radial coords and finding
    % corresponding r index
    ind_r = round(sqrt(x^2 + y^2) / input(2).grid_sep);
    % optimize r index for comparison, eq. 4.2, resp. 8
    r = ((ind_r + 0.5) + 1 / (12 * (ind_r + 0.5)))*delta_r;
    
    % find angle along z and corresponding alpha index
    ind_alpha = round(acos(abs(photon_packet(3).dir_cosines)) / input(3).grid_sep);
    % optimize alpha index for comparison, eq. 4.1, resp. 14
    alpha = (ind_alpha + 0.5)*delta_alpha + cot((ind_alpha + 0.5)*delta_alpha) ...
        * (1 - (delta_alpha/2)*cot(delta_alpha/2));
        
    % r and alpha index optimalization
    % optimized r and alpha we have are "centers" of each index
    % we can therefore move the calculated indices up or down by 1 depending
    % on the comparison with the optimized indices
    
    if(ind_alpha >= alpha)
        ind_alpha = ceil(ind_alpha);
    else
        ind_alpha = floor(ind_alpha);
    end
    if(ind_r >= r)
        ind_r = ceil(ind_r);
    else
        ind_r = floor(ind_r);
    end
   
    % if out of range, count as top or bottom index
    if(ind_r > input(2).grid_range)
        ind_r = input(2).grid_range;
    elseif(ind_r < 1)
        ind_r = 1;
    end
    if(ind_alpha > input(3).grid_range)
        ind_alpha = input(3).grid_range;
    elseif(ind_alpha < 1)
        ind_alpha = 1;
    end    
    
    % eq. 3.35, z condition implemented by metric distance because of
    % precision
    if(photon_packet(1).scatters > 0)
        if((photon_packet(3).cart_coord - layer(1).z_coord)^2 < (photon_packet(3).cart_coord - layer(2).z_coord)^2)
            output.Rd_r_alpha(ind_r, ind_alpha) = output.Rd_r_alpha(ind_r, ind_alpha) + ...
                photon_packet(1).weight*(1 - R_alpha);
        else
            output.Td_r_alpha(ind_r, ind_alpha) = output.Td_r_alpha(ind_r, ind_alpha) ...
                + photon_packet(1).weight*(1 - R_alpha);
        end
    elseif(photon_packet(1).scatters == 0)
        if((photon_packet(3).cart_coord - layer(1).z_coord)^2 < (photon_packet(3).cart_coord - layer(2).z_coord)^2)           
            output.Rd_r(N_r+1) = output.Rd_r(N_r+1) + photon_packet(1).weight*(1 - R_alpha); 
        else
            output.Td_r(N_r+1) = output.Td_r(N_r+1) + photon_packet(1).weight*(1 - R_alpha);
        end       
    end
end

%% play termination roulette if weight below threshold 0.0001
% acc. to p. 10
function [photon_packet, survived] = russianRoulette(photon_packet, roulette_weight)
    ksi = genRandomUniformNumber();
    % eq. 3.36
    if(ksi <= 1 / roulette_weight)
        photon_packet(1).weight = roulette_weight * photon_packet(1).weight;
        survived = true;
    else
        photon_packet(1).weight = 0;
        photon_packet(1).dead = true;
        survived = false;
    end
end

%% calculate final Rd_r, Td_r, Rd_alpha, Td_alpha, Rd, Td
% acc. to p. 11
function [output] = calcResults(input, layer, output)
    N = input(1).num_of_photons;
    N_r = input(2).grid_range;
    N_alpha = input(3).grid_range;
    delta_alpha = input(3).grid_sep;
    Rsp = output.Rsp;
    mu_a = layer(1).absorb_coeff;
    mu_s = layer(1).scatter_coeff;
    
    % eqs 4.1, 4.11, 4.12
    alpha = @(i) (i+0.5)*delta_alpha + cot((i+0.5)*delta_alpha)*...
        (1 - (delta_alpha/2)*cot(delta_alpha/2));
    delta_a = @(i) 2*pi*(i + 0.5)*(input(2).grid_sep)^2;
    delta_omega = @(i) 4*pi*sin((i+0.5)*input(3).grid_sep)*sin(input(3).grid_sep/2);
        
    for i = 1:N_r
        d_a = delta_a(i);
        sum_Rd_r = 0; sum_Td_r = 0;
        % eqs. 4.3, 4.5
        for j = 1:N_alpha
            sum_Rd_r = sum_Rd_r + output.Rd_r_alpha(i, j);
            sum_Td_r = sum_Td_r + output.Td_r_alpha(i, j);
        end
        output.Rd_r(i) = sum_Rd_r;
        output.Td_r(i) = sum_Td_r;
        % eqs. 4.7, 4.8
        output.Rd = output.Rd + output.Rd_r(i);
        output.Td = output.Td + output.Td_r(i);
        % eqs. 4.13, 4.14
        output.Rd_r(i) = output.Rd_r(i)/(d_a*N);
        output.Td_r(i) = output.Td_r(i)/(d_a*N);
    end    
      
    for i = 1:N_alpha
        d_omega = delta_omega(i);
        al = alpha(i);
        sum_Rd_alpha = 0; sum_Td_alpha = 0;
        for j = 1:N_r
            d_a = delta_a(j);           
            % eqs. 4.4, 4.6
            sum_Rd_alpha = sum_Rd_alpha + output.Rd_r_alpha(j, i);
            sum_Td_alpha = sum_Td_alpha + output.Td_r_alpha(j, i);            
            % eqs. 4.9, 4.10
            output.Rd_r_alpha(j, i) = output.Rd_r_alpha(j, i)/(d_a*cos(al)*d_omega*N);
            output.Td_r_alpha(j, i) = output.Td_r_alpha(j, i)/(d_a*cos(al)*d_omega*N);
        end
        output.Rd_alpha(i) = sum_Rd_alpha;
        output.Td_alpha(i) = sum_Td_alpha;
        % eqs. 4.15, 4.16
        output.Rd_alpha(i) = output.Rd_alpha(i)/(d_omega*N);
        output.Td_alpha(i) = output.Td_alpha(i)/(d_omega*N);
    end
    
    % par. below eq. 4.14
    output.Rd_r(N_r+1) = Rsp + output.Rd_r(N_r+1)/N;
    output.Td_r(N_r+1) = output.Td_r(N_r+1)/N;
    
    % eqs. 4.17, 4.18
    output.Rd = output.Rd/N;
    output.Td = output.Td/N;
    
    % p. 13 bottom right
    output.Td_unscattered = exp(-(mu_a + mu_s)*layer(1).thickness);
    output.Td_diffuse = output.Td - output.Td_unscattered;
end
