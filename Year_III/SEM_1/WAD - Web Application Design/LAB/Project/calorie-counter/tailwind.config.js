module.exports = {
  mode: 'jit',
  content: [
    "./pages/**/*.{js,ts,jsx,tsx}",
    "./components/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      fontFamily: {
        site: ['Roboto', 'sans-serif'],
        "futura-book": ['FuturaBTW01-Book', 'sans-serif'],
        "futura-light": ['FuturaBTW01-Light', 'sans-serif'],
      },
      keyframes: {
        'load': {
          '0%, 100%': {
            transform: 'scale(1)'
          },
          '50%': {
            background: '#bbf',
            transform: 'scale(4)'
          }
        }
      },
      animation: {
        'load-1': '2.5s load 0.2s cubic-bezier(.71,.16,.25,.83) infinite',
        'load-2': '2.5s load 0.4s cubic-bezier(.71,.16,.25,.83) infinite',
        'load-3': '2.5s load 0.6s cubic-bezier(.71,.16,.25,.83) infinite', 
        'load-4': '2.5s load 0.8s cubic-bezier(.71,.16,.25,.83) infinite',
        'load-5': '2.5s load 1.0s cubic-bezier(.71,.16,.25,.83) infinite',
      }
    },
  },
  plugins: [],
}
