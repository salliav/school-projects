import React from 'react';
import {BrowserRouter, Routes, Route} from 'react-router-dom';
import {CssBaseline, Container, Box, Typography} from '@mui/material';
import {ThemeProvider} from '@mui/material/styles';
import theme from './theme/Theme';
import Home from './pages/Home';
import RecipeDetails from './pages/RecipeDetails';


/**
 * Main component App for holding the pages Home and RecipeDetails.
 * Takes care of routing between the pages.
*/
function App() {
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline/>
      <Box sx={{
            width: '70%',
            minHeight: '100vh',
            margin: 'auto',
            backgroundColor: 'rgba(255, 255, 255, 0.9)',
            padding: '40px'
      }}>
        <BrowserRouter>
          <Container style={{marginTop:'40px', marginBottom:'40px'}}> 
            <Typography variant="h1" gutterBottom>Recipe Finder</Typography>
            <Box style={{width: '100%'}}>
              <Routes>
                <Route path="/" element={<Home/>}/>
                <Route path="/recipedetails/:id" element={<RecipeDetails/>}/>
              </Routes>
            </Box>
          </Container>
        </BrowserRouter>
      </Box>
    </ThemeProvider>
  );
}

export default App;

