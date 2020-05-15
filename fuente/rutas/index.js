  //En este archivo se generan las rutas de acceso del sitio web según el cliente solicite 
const express = require('express');
const router = express.Router();

router.get('/', (req, res) => {
  res.render('index', { title: 'Somos SCHUNK',
  webinar1: ""






});
});

router.get('/privacidad', (req, res) => {
  res.render('privacidad', { nav: 'Regresar a inicio',
  webinar1: "", title: "Política de privacidad"


});
});



module.exports = router;
