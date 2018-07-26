const path = require('path');
const outputDir = path.join(__dirname, "public/");

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './lib/js/src/Index.js',
  mode: isProd ? 'production' : 'development',
  devtool: "cheap-eval-source-map",
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'bundle.js',
  },
};
