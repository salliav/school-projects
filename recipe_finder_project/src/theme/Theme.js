import {createTheme} from "@mui/material/styles";


/**
 * Theme that defines styles for texts, MUI components and backgrounds.
*/
const theme = createTheme({
    palette: {
      background: {
        default: '#fad7e1',
      },
      primary: {
        main: '#e81e5b',
      },
      secondary: {
        main: '#f78f20',
      },
      text: {
        primary: '#333333',
        secondary: '#666666',
      },
    },
    typography: {
      fontFamily: 'Arial, sans-serif',
      h1: {
        fontSize: '4.0rem',
        fontWeight: 600,
        textShadow: '2px 2px 4px rgba(0, 0, 0, 0.5)'
      },
      h2: {
        fontSize: '2.0rem',
        fontWeight: 550,
      },
      h3: {
        fontSize: '1.2rem',
        fontWeight: 550,
        lineHeight: 1.75
      },
      body1: {
        fontSize: '1.2rem',
        lineHeight: 1.75,
      },
      body2: {
        fontSize: '1.0rem',
        lineHeight: 1.5,
      }
    },
    components: {
      MuiCssBaseline: {
        styleOverrides: {
          body: {
            backgroundImage: 'url(/backgroundImage.jpg)',
            backgroundSize: 'cover',
            backgroundPosition: 'center',
            backgroundRepeat: 'no-repeat',
            minHeight: '100vh',
            margin: 0,
            padding: 0,
            backgroundAttachment: 'fixed'
          }
        }
      },
      MuiCard: {
        styleOverrides: {
          root: {
            background: '#f78f20'
          }
        }
      },
      MuiButton: {
        styleOverrides: {
          root: {
            fontSize: '18px',
            fontWeight: 600,
            color: '#333333',
            background: 'linear-gradient(to right, #e81e5b, #f78f20)',
            padding: '10px 20px',
            textTransform: 'uppercase',
            borderRadius: '10px',
            whiteSpace: 'nowrap',
            boxShadow: '0px 0px 5px 0px #666666'
          },
        },
      },
      MuiTypography: {
        styleOverrides: {
          h1: {
            color: '#e81e5b',
          },
        },
      },
    },
  });

export default theme;