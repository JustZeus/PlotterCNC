

// configutación de recursos.
require('dotenv').config();

const express = require('express');
const morgan = require('morgan');
const path = require('path');
const sendMail = require('./mail');
const { log } = console;
const app = express();

// configuración
app.set('puerto', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
// middlewares
app.use(morgan('dev'));







// rutas
app.use(require('./rutas'));

app.use(express.urlencoded({
  extended: false
}));
app.use(express.json());


app.post('/email', (req, res) => {
  const { subject, email, text } = req.body;
  log('Data: ', req.body);

  sendMail(email, subject, text, function(err, data) {
      if (err) {
          log('ERROR: ', err);
          return res.status(500).json({ message: err.message || 'Internal Error' });
      }
      log('Email sent!!!');
      return res.json({ message: 'Email sent!!!!!' });
  });
});
// archivos estaticos (imagenes y demas recursos)
app.use(express.static(path.join(__dirname, 'public')));




// servidor escuchando
app.listen(app.get('puerto'), () => {
  console.log('Servidor en el puerto', app.get('puerto'));
});