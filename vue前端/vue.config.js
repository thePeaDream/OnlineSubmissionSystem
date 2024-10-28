module.exports = {
  devServer: {
    webSocketServer: false,
    proxy: {
      '/': {
        target: 'http://114.132.234.12:8080',
        changeOrigin: true,
        pathRewrite: {
          '^/': ''
        }
      }
    }
  },
  assetsDir:'static',
  parallel:false,
  publicPath:'./',
  transpileDependencies: true,
  lintOnSave: false,
};


