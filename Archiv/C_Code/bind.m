function [] = bind()
    coder.cinclude('simulate.h');
    
    v = coder.ceval('simulate');
    
    disp(v)
    
end

