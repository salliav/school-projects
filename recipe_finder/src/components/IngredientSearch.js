import {React, useEffect, useState} from "react";
import {createFilterOptions} from "@mui/material";
import {Autocomplete, TextField, Snackbar} from "@mui/material";



// Helper function for creating a list of ingredients out of the CSV file
const parseCSV = (text) => {
  const lines = text.trim().split('\n');
  const result = [];
  for (let i = 0; i < lines.length; i++) {
    const word = lines[i].trim();
    const splitted = word.split(';');
    result.push(splitted[0]);
  }
  return result;
}

/**
 * Ingredient search field for selecting ingredients from an autocompleted
 * list of options. Gets the list by generating it from the file ingredients.csv.
 * Transfers the selected ingredients for SearchBar component.
 * @param {array} selectedIngredients - empty array that stores user's selections
 * @param {function} setSelectedIngredients - setter function for storing user's selections
 * @returns MUI Autocomplete component that holds ingredient options
 */
function IngredientSearch({selectedIngredients, setSelectedIngredients}) {
    
  const [ingredientList, setIngredientList] = useState([]);
  const [showSnackbar, setShowSnackbar] = useState(false);

  useEffect(() => {
      const fetchData = async () => {
        try {
          const response = await fetch('/ingredients.csv');
          const text = await response.text();
          const wordsArray = parseCSV(text);
          setIngredientList(wordsArray);
        } catch (error) {
          console.error('Error fetching CSV:', error);
        }
      };  

      fetchData();
    }, [])


  const handleIngredientChange = (event, newValue) => {
    
    // Snackbar shows a message for the user if too many ingredients have been selected. 
    if (newValue.length <= 6) {
      setSelectedIngredients(newValue);
      setShowSnackbar(false);
    } else {
      setShowSnackbar(true);
    }
  }
      

  return (
    <>
      <Autocomplete
        multiple
        options={ingredientList}
        filterOptions={createFilterOptions({limit: 50})}
        getOptionLabel={(option) => option}
        disableCloseOnSelect={true}
        value={selectedIngredients}
        onChange={handleIngredientChange}
        renderInput={(params) =>
            <TextField {...params} label="Ingredients" style={{width:'80%'}}/>
        }
        renderOption={(props, option, state) => (
            <li {...props} key={`${option}-${state.index}`}>{option}</li>
        )}
      />
      {showSnackbar && (
        <Snackbar
          open={showSnackbar}
          autoHideDuration={7000}
          onClose={() => setShowSnackbar(false)}
          message="Sorry, 6 ingredients is the maximum."
        />
      )}
    </>
  )
}

export default IngredientSearch;