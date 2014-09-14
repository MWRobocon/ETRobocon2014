function [ sph_calibration_angle ] = sphero_calib( sph, vid )
%SPHERO_CALIB Calibration of the orientation of the Sphero with camera frame

    roll(sph, 70, 0);

    framenum = 1;
    spheropos = zeros(10, 2);

    while(framenum<=10)
        frame = step(vid);
        [~, spheropos(framenum, :)] = detectMinions2(frame);

        framenum = framenum+1;
    end

    brake(sph);

    spheropos_extract = reshape(spheropos(spheropos~=-1), [], 2);

    spheropos_extract = [spheropos_extract(:, 1) -spheropos_extract(:, 2)];

    linefit = fit(spheropos_extract(:, 1), spheropos_extract(:, 2), 'poly1');
    linefit_theta = mod(atand(linefit.p1), 360);
    linefit_theta180 = mod(linefit_theta+180, 360);


    theta_degrees = mod(atan2d(spheropos_extract(end, 2)-spheropos_extract(1, 2), spheropos_extract(end, 1)-spheropos_extract(1, 1)), 360);
    
    diffAngle = abs(theta_degrees-linefit_theta);
    diffAngle180 = abs(theta_degrees-linefit_theta180);

    if diffAngle<10
        sph_calibration_angle = mod(-90-linefit_theta, 360);
    elseif diffAngle180<10
        sph_calibration_angle = mod(-90-linefit_theta180, 360);
    else
        sph_calibration_angle = 0;
        warning('Please re-calibrate. Enough data for calibration not received');
    end

end

