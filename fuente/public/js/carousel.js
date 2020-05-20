$(document).ready(function() {
 
    $("#owl-demo").owlCarousel({
   
        navigation : false, // Show next and prev buttons
   
        slideSpeed : 250,
        paginationSpeed : 400,
   
        items : 1, 
        itemsDesktop : false,
        itemsDesktopSmall : false,
        itemsTablet: false,
        itemsMobile : false,
        loop:true,
        margin:10,
        autoplay:true,
        autoplayTimeout:4000,
        autoplayHoverPause:true
   
    });
   
  });


    ScrollReveal().reveal('.row', { delay: 500,  duration: 1050  });
  
