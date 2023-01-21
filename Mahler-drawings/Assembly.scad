include <case.scad>
include<tappo-case.scad>

// Case 
color("blue",1)
    translate([L,0,L])
        rotate([0,180,0])
            case();
 // Tappo
 color("yellow",1)
    tappocase();

 
 
 
 


 