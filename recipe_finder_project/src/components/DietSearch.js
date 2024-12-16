import {React, useState} from "react";
import {Select, Checkbox, MenuItem, ListItemText, InputLabel, FormControl, Snackbar } from "@mui/material";


const dietOptions = [
  'gluten free',
  'ketogenic',
  'vegetarian',
  'lacto-vegetarian',
  'ovo-vegetarian',
  'vegan',
  'pescetarian',
  'paleo',
  'primal',
  'low FODMAP',
  'whole30'
];


/**
 * Diet search field for selecting diets from a list. Transfers the selected diets
 * for SearchBar component.
 * @param {array} selectedDiets - empty array that stores user's selections
 * @param {function} setSelectedDiets - setter function for storing user's selections
 * @returns Formcontrol component with MUI Select holding
 * diet name options.
 */
function DietSearch({selectedDiets, setSelectedDiets}) {
  
  const [showSnackbar, setShowSnackbar] = useState(false);

  
  const handleChange = event => {
    const value = event.target.value;

    // Snackbar shows a message for the user if too many diets have been selected. 
    if (value.length <= 3) {
      setSelectedDiets(value);
      setShowSnackbar(false);
    } else {
      setShowSnackbar(true);
    }
  };


  return (
    <>
      <FormControl>
        <InputLabel id="dietLabel">Diets</InputLabel>
        <Select
          multiple
          labelId="dietLabel"
          id="dietSelect"
          label="Diets"
          style={{width: '80%'}}
          value={selectedDiets}
          onChange={handleChange}
          renderValue={(selected) => selected.join(', ')}>
            {dietOptions.map(diet =>
              <MenuItem key={diet} value={diet}>
                <Checkbox checked={selectedDiets.indexOf(diet) > -1} />
                <ListItemText>{diet}</ListItemText>
              </MenuItem>)}
        </Select>
      </FormControl>
        {showSnackbar && (
          <Snackbar
            open={showSnackbar}
            autoHideDuration={7000}
            onClose={() => setShowSnackbar(false)}
            message="Sorry, 3 diets is the maximum."
          />
        )}
      </>
  )
}

export default DietSearch;