  //En este archivo se generan las rutas de acceso del sitio web según el cliente solicite 
const express = require('express');
const router = express.Router();

router.get('/', (req, res) => {
  res.render('index', { title: 'Somos SCHUNK',
  webinar1: "https://us02web.zoom.us/meeting/register/tZIucOCoqDgqGtJRLqSWKy4E63j6CY3FPbux",
  webinar2:"https://us02web.zoom.us/meeting/register/tZYuc--uqDsoE9Qg2W5HgMTdgmvZAupKUQ2Y",
  webinar3:"https://us02web.zoom.us/meeting/register/tZwtde6rpjwqGNDmWxPU_tk2UD1WYTuxTcXe",
  webinar4:"https://us02web.zoom.us/meeting/register/tZUpce6rrDoiG9wyxfguo7cCRK79_r7QoFKq",
  webinar5:"https://us02web.zoom.us/meeting/register/tZwkcuqurDMjHNIRdgurjj8aLM0PPvmW6kgS",
  webinar6:"https://us02web.zoom.us/meeting/register/tZIvcemtrzosH9VOKmGApiACu52CclXAuahJ",
  webinar7:"https://us02web.zoom.us/meeting/register/tZwrfuCrrTsoHNUr2rul8iRbgM73pLOHfCOu",
  webinar8:"https://us02web.zoom.us/meeting/register/tZAvfuqhpz8uHdNwZVGJdGhrDn0L_tqLPtjw",
  webinar9:"https://us02web.zoom.us/meeting/register/tZIofuuorT4oG9bZegTmqTI6pu6Hm9z7uiZf",
  webinar10:"https://us02web.zoom.us/meeting/register/tZIkd-Crrj4jE9PdnzRuB8J9qzKnuYXwsuZl",
 

});
});

router.get('/privacidad', (req, res) => {
  res.render('privacidad', { nav: 'Regresar a inicio',
  title: "Política de privacidad"
});
});



module.exports = router;
