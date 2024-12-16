import React, {useEffect, useState} from "react";
import {Box, Button, Typography, Stack, Grid} from "@mui/material";
import {useNavigate, useParams} from "react-router-dom";
import parse from "html-react-parser";
import {API_KEY} from "../services/api";


/**
 * RecipeDetails page for displaying detailed information of
 * the selected recipe. Performs an API call with the received
 * recipe ID. Displays an error message in case of unsuccesful 
 * API response, otherwise displays the recipe with the image,
 * ingredients and instructions.
 * @returns MUI Stack with a button and recipe content.
 */
function RecipeDetails() {
    const navigate = useNavigate();
    let {id} = useParams();
    const [recipe, setRecipe] = useState([]);
    const [ingredients, setIngredients] = useState([]);
    const [instructions, setInstructions] = useState('');
    const [responseOk, setResponseOk] = useState(true);

    useEffect(() => {
        async function fetchRecipeDetails() {
            try {
                const response = await fetch(`https://api.spoonacular.com/recipes/${id}/information?includeNutrition=false&apiKey=${API_KEY}`);
                setResponseOk(response.ok);
                if (!response.ok) {
                  throw new Error(`Network response was not ok: ${response.status}`);
                }
                const data = await response.json();
                setRecipe(data);
                setIngredients(data.extendedIngredients || []);
                setInstructions(data.instructions || '');
            } catch (error) {
                console.error("Error fetching the recipe details, ", error);
            }
        }
        fetchRecipeDetails();
    }, []);


    return (
      <Stack display="flex" gap={6} sx={{padding: 2}}>
         
        <Box display="inline-flex" alignItems="center">
          <Button 
            variant="contained"
            sx={{whiteSpace: 'nowrap', width:'auto'}}
            onClick={() => navigate(-1)}
            >
              Back To Results
            </Button>
        </Box>


        {!responseOk ? (
          <Typography variant="h6" color="error">
            Sorry, we were unable to retrieve the recipe details at the moment. Please try again later.
          </Typography>
        ) : (
          <>
            <Stack display="flex" gap={4}>
              <Typography variant="h2">{recipe.title}</Typography>
              <Typography variant="body1">
                Serving size: {recipe.servings} | Cooking time: {recipe.readyInMinutes} min
              </Typography>
            </Stack>

            <Box
              display="flex"
              justifyContent="space-between"
              alignItems="flex-start"
              gap={4}
              sx={{flexDirection: {xs: 'column', md: 'row'}}}
            >
              {/* Ingredient names and their amounts are displayed in grid structure.*/}
              <Box flex={1} pr={1}>
                <Typography variant="h3" sx={{mb: 2}}>Ingredients</Typography>
                {ingredients.map((item, index) => (
                  <Grid
                    container
                    key={`${item.name}-${index}`}
                    spacing={2}
                    alignItems="center"
                    width="100%"
                    >
                    <Grid item xs={6} md={4}>
                      <Typography id={`${item.id}-${index}`}>
                        {item.amount} {item.measures.metric.unitShort}
                      </Typography>
                    </Grid>
                    <Grid item xs={6} md={8}>
                      <Typography>{item.name}</Typography>
                    </Grid>
                  </Grid>
                ))}
              </Box>

              <Box flex={1} pl={1}>
                <img
                  src={recipe.image}
                  alt={recipe.title}
                  style={{width: '100%', maxWidth: '600px', height: 'auto', display: 'block'}}
                  />
              </Box>
            </Box>

            <Box>
              <Typography variant="h3" sx={{mb: 2}}>Instructions</Typography>
              <Typography component="div" variant="body1">{parse(instructions)}</Typography>
            </Box>
          </>
        )}
      </Stack>
  );
}

export default RecipeDetails;