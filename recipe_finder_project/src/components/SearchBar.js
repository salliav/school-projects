import {React, useState} from 'react';
import {Box, Typography, Stack, Button} from '@mui/material';
import RecipeList from './RecipeList';
import DietSearch from './DietSearch';
import IngredientSearch from './IngredientSearch';
import DishSearch from './DishSearch';


/**
 * SearchBar component for holding serach field components and
 * rendering the search result list. Receives the search params from other components
 * and transmits them for ResultList component.
 * @returns MUI Box containing search field components and ResultList component.
 */
function SearchBar() {

  const [selectedDish, setSelectedDish] = useState('');
  const [dishParam, setDishParam] = useState('');
  const [selectedIngredients, setSelectedIngredients] = useState([]);
  const [ingredientParams, setIngredientParams] = useState('');
  const [selectedDiets, setSelectedDiets] = useState([]);
  const [dietParams, setDietParams] = useState('');


  const handleSearchParams = () => {
    const modifiedIngredients = selectedIngredients.map(ingredient => encodeURIComponent(ingredient)).join(',+');
    const modifiedDiets = selectedDiets.map(diet => encodeURIComponent(diet)).join(',');
    const modifiedDish = encodeURIComponent(selectedDish);

    setIngredientParams(modifiedIngredients);
    setDietParams(modifiedDiets);
    setDishParam(modifiedDish);

    console.log('SearchBar, IngredientParams:', ingredientParams);
    console.log('SearchBar, dietParams:', dietParams);
    console.log('SearchBar, dishParam:', dishParam);
  }


  const emptySearchParams = () => {
    setSelectedDiets([]);
    setSelectedIngredients([]);
    setSelectedDish('');
    
    sessionStorage.removeItem(`storedIngredientParams`);
    sessionStorage.removeItem(`storedDietParams`);
    sessionStorage.removeItem(`storedDishParam`);
  }


  return (
    <Box
      sx={{
      width: '100%',
      display: 'flex',
      flexDirection:  {xs: 'column', md: 'row'},
      justifyContent: 'space-between',
      gap: 2
      }}>
      <Stack spacing={3} sx={{flex: 1 }}>    
        <Typography variant='body2'>
          Search for recipes by <br/> ingredients, dietary preferences, and dish names
        </Typography>

        <DishSearch selectedDish={selectedDish} setSelectedDish={setSelectedDish}/>

        <DietSearch selectedDiets={selectedDiets} setSelectedDiets={setSelectedDiets}/>

        <IngredientSearch selectedIngredients={selectedIngredients} setSelectedIngredients={setSelectedIngredients}/>

        <Box display="flex" gap={2} justifyContent="space-between" style={{width:'80%'}}>
          <Button variant="contained" onClick={() => emptySearchParams()}> Empty </Button>
          <Button variant="contained" onClick={() => handleSearchParams()}> Search </Button>
        </Box>
      </Stack>

      <Box sx={{flex: 1, mt: {xs: 4, md: 0}}}>
        <RecipeList
          dishParam={dishParam}
          ingredientParams={ingredientParams}
          dietParams={dietParams}/>
      </Box>
    </Box>
  );
}

export default SearchBar;