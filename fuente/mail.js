const nodemailer = require('nodemailer');
const mailGun = require('nodemailer-mailgun-transport');

const auth = {
    auth: {
        api_key: process.env.API_KEY ||  'b04b0f1508b2c0ca30f440c57295b62c-f135b0f1-5d398d74', // TODO: Replace with your mailgun API KEY
        domain: process.env.DOMAIN || 'sandbox47747425b22d4d42b1e03bbe8833e14a.mailgun.org' // TODO: Replace with your mailgun DOMAIN
    }
};

const transporter = nodemailer.createTransport(mailGun(auth));


const sendMail = (email, subject, text, cb) => {
    const mailOptions = {
        from: email, // TODO replace this with your own email
        to: 'somoschunk@gmail.com', // TODO: the receiver email has to be authorized for the free tier
        subject,
        text
    };

    transporter.sendMail(mailOptions, function (err, data) {
        if (err) {
            return cb(err, null);
        }
        return cb(null, data);
    });
}

module.exports = sendMail;