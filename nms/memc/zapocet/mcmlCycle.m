%% help
% calls MCML cycle the input number of times, then sums, averages and plots
% results. results saved as a fig and as data as required by a credit assignment, 
% see relevant fig. 3 on p. 14 in MCML paper

%% cycle mcml by user input
% photon_packet, layer, input are preset from MCML paper
function [] = mcmlCycle(num_of_cycles)
    % photon packet structure and init acc. to p. 5 and own necesarry defs
    % cart_coord and dir_cosines ordering: x, y, z
    photon_packet = struct('cart_coord', {0, 0, 0}, 'dir_cosines', {0, 0, 1}, ...
        'weight', 1, 'dead', true, 'step_size', 0, 'scatters', 0, 'layer', 1);

    % layer structure according to p. 2 and init acc. to p. 13
    layer = struct('z_coord', {0, 0.02}, 'refr_ind', 1, 'absorb_coeff', 10, ...
        'scatter_coeff', 90, 'anisotropy', 0.75, 'thickness', 0);
    layer(1).thickness = layer(2).z_coord - layer(1).z_coord;

    % input structure acc. to p. 4, init acc. to p. 13
    % grid_sep (deltas) and grid_range (number of deltas) are ordered: z, r, alpha
    input = struct('num_of_photons', 50000, 'roulette_weight', 10, 'grid_sep', {0.001, 0.001, 0}, ...
         'grid_range', {15, 15, 30}, 'num_of_layers', 2, ...
         'refr_ind_medium', 1, 'refr_ind_clearLayer', 1.5168);
    % delta_alpha acc. to p. 3, top right
    input(3).grid_sep = pi / (2 * input(3).grid_range);
    
    fprintf('Simulating %d photon packet(s) in %d cycle(s)! \n', input(1).num_of_photons, num_of_cycles);
    
    % get results per run
    res_per_run = cell(num_of_cycles, 1);
    tic;
    for i = 1:num_of_cycles
       res_per_run{i, 1} = mcml(input, photon_packet, layer);
       fprintf('Cycle %d out of %d finished! \n', i, num_of_cycles);
    end
    toc;

    % sum and average relevant data
    N_r = input(2).grid_range;
    N_alpha = input(3).grid_range;
    Rd = 0; Td = 0; Td_unscattered = 0; Td_diffuse = 0;
    % +1 is for unscattered photon weight acc. to p. 10 above eq. 4.1
    Rd_r = zeros(N_r+1); Td_r = zeros(N_r+1); 
    Rd_alpha = zeros(N_alpha); Td_alpha = zeros(N_alpha);
    for i = 1:num_of_cycles
        Rd = Rd + res_per_run{i, 1}.Rd(1);
        Td = Td + res_per_run{i, 1}.Td(1);
        Td_unscattered = Td_unscattered + res_per_run{i, 1}.Td_unscattered(1);
        Td_diffuse = Td_diffuse + res_per_run{i, 1}.Td_diffuse(1);
        Rd_r = Rd_r + res_per_run{i, 1}.Rd_r(:, 1);
        Td_r = Td_r + res_per_run{i, 1}.Td_r(:, 1);
        Rd_alpha = Rd_alpha + res_per_run{i, 1}.Rd_alpha(:, 1);
        Td_alpha = Td_alpha + res_per_run{i, 1}.Td_alpha(:, 1);
    end
    % average through number of cycles
    Rd = Rd / num_of_cycles;
    Td = Td / num_of_cycles;
    Td_unscattered = Td_unscattered / num_of_cycles;
    Td_diffuse = Td_diffuse / num_of_cycles;
    Rd_r = Rd_r(:, 1) / num_of_cycles;
    Td_r = Td_r(:, 1) / num_of_cycles;
    Rd_alpha = Rd_alpha(:, 1) / num_of_cycles;
    Td_alpha = Td_alpha(:, 1) / num_of_cycles;
    
    fprintf('Final results: \n Rd = %.5f, \n Td = %.5f, \n Td_unscattered = %.5f, \n Td_diffuse = %.5f \n', Rd, Td, ...
        Td_unscattered, Td_diffuse);
    
    % create output structure and plot - other ouput values are irrelevant for
    % credit assignment, which consists in replication of fig. 3 on p. 13
    output = struct('Rd', Rd, 'Td', Td, 'Td_unscattered', Td_unscattered, ...
        'Td_diffuse', Td_diffuse, 'Rd_r', Rd_r, 'Td_r', Td_r, ...
        'Rd_alpha', Rd_alpha, 'Td_alpha', Td_alpha);
    
    mkdir results;
    writeData(input, output, num_of_cycles);
    plotResults(input, output, num_of_cycles);
end

%% save data output
% desired output values, p. 13:
% Rd = 0.09739
% Td = 0.66096
% Td_unscattered = 0.13534
% Td_diffuse = 0.52562
function [] = writeData(input, output, num_of_cycles)
    num_of_cycles_str = num2str(num_of_cycles);
    num_of_photons_str = num2str(input(1).num_of_photons);
    filename = strcat('resultMCML_photons_', num_of_photons_str, ...
        '_cycles_', num_of_cycles_str, '.mat');
    save(['results\' filename], 'output');     
end

%% plot and save graph
function [] = plotResults(input, output, num_of_cycles)
    f = figure('Name', 'Results for MCML');

    % plot from 0 to pi/2 for escape angle
    x = (pi/(2*input(3).grid_range)):(pi/(2*input(3).grid_range)):pi/2;
    % two subplots for Rd_alpha, Td_alpha
    subplot(2, 1, 1);
    y1 = output.Rd_alpha(:, 1);
    plot(x, y1, 'rs');
    legend('MCML');
    xlabel('Exit angle \alpha [rad]');
    set(gca,'XTick',0:pi/10:pi/2) 
    set(gca,'XTickLabel',{'0\pi','0.1\pi','0.2\pi','0.3\pi', '0.4\pi', '0.5\pi'})
    ylabel('R_{d}(\alpha) [sr^{-1}]')
    set(gca, 'YTick', 0:0.005:0.025);
    set(gca, 'YTickLabel', {'0', '0.005', '0.01', '0.015', '0.02', '0.025'});
    pbaspect([1 1 1]);
    
    subplot(2, 1, 2);
    y2 = output.Td_alpha(:, 1);
    plot(x, y2, 'gs');
    legend('MCML');
    xlabel('Exit angle \alpha [rad]');
    set(gca,'XTick',0:pi/10:pi/2) 
    set(gca,'XTickLabel',{'0\pi','0.1\pi','0.2\pi','0.3\pi', '0.4\pi', '0.5\pi'})
    ylabel('T_{d}(\alpha) [sr^{-1}]')
    set(gca, 'YTick', 0:0.2:0.8);
    set(gca, 'YTickLabel', {'0', '0.2', '0.4', '0.6', '0.8'});
    pbaspect([1 1 1]);
    
    % save fig
    num_of_cycles_str = num2str(num_of_cycles);
    num_of_photons_str = num2str(input(1).num_of_photons);
    filename = strcat('plotMCML_photons_', num_of_photons_str, ...
        '_cycles_', num_of_cycles_str, '.fig');
    savefig(f, ['results\' filename]);
end