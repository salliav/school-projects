import {React, useState, useEffect } from "react";
import {Stack, Card, Button, CardContent, Typography, Pagination} from '@mui/material';
import {useNavigate} from "react-router-dom";
import {API_KEY} from "../services/api";



/**
 * RecipeList component displays the retrieved recipes in a list. Receives
 * the search parameters from SearchBar component and generates the result list
 * from API call response.
 * @param {string} dishParam - encooded URI component for selected dish
 * @param {string} ingredientParams - encooded URI component for selected ingredients
 * @param {string} dietParams - encooded URI component for selected diet 
 * @returns MUI Stack containing list of recipe cards
 */
function RecipeList({dishParam, ingredientParams, dietParams}) {
    
    const navigate = useNavigate();
    const [recipes, setRecipes] = useState([]);
    const [searched, setSearched] = useState(false);
    const [responseOk, setResponseOk] = useState(true);
    const [currentPage, setCurrentPage] = useState(1);


    // hakee storagesta vain jos hakuparametreja ei ole annettu
    useEffect(() => {
        async function fetchRecipes() {
            
            console.log('FetchRecipes called.');

            let currentIngredientParams = ingredientParams;
            let currentDietParams = dietParams;
            let currentDishParam = dishParam;

            console.log('Current Ingredient Params:', currentIngredientParams);
            console.log('Current Diet Params:', currentDietParams);
            console.log('Current Dish Param:', currentDishParam);
            
            // When the program navigates from RecipeDetails back to Home, search parameters
            // are erased and an api call is made using stored search aparameters for showing
            // the previous results.
            // Otherwise, if some new search parameters have been set by the user,
            // those parameters are stored. 
            if (currentIngredientParams === '' && currentDietParams === '' && currentDishParam === '') {
                currentIngredientParams = sessionStorage.getItem(`storedIngredientParams`) || '';
                currentDietParams = sessionStorage.getItem(`storedDietParams`) || '';
                currentDishParam = sessionStorage.getItem(`storedDishParam`) || '';
            } else {
                sessionStorage.setItem(`storedIngredientParams`, currentIngredientParams);
                sessionStorage.setItem(`storedDietParams`, currentDietParams);
                sessionStorage.setItem(`storedDishParam`, currentDishParam);
            }

            console.log('Stored Ingredient Params:', sessionStorage.getItem(`storedIngredientParams`));
            console.log('Stored Diet Params:', sessionStorage.getItem(`storedDietParams`));
            console.log('Stored Dish Param:', sessionStorage.getItem(`storedDishParam`));

            // API call is made only when some search parameters are set
            if (currentIngredientParams !== '' || currentDietParams !== '' || currentDishParam !== '') {
                try {
                    setSearched(true);
                    const response = await fetch(`https://api.spoonacular.com/recipes/complexSearch?query=${encodeURIComponent(currentDishParam)}&includeIngredients=${encodeURIComponent(currentIngredientParams)}&diet=${encodeURIComponent(currentDietParams)}&instructionsRequired=true&number=41&apiKey=${API_KEY}`);
                    setResponseOk(response.ok);
                    const data = await response.json();
                    setRecipes(data.results || []);
    
                    console.log('Stored Ingredient Params after setting recipes:', sessionStorage.getItem(`storedIngredientParams`));
                    console.log('Stored Diet Params after setting recipes:', sessionStorage.getItem(`storedDietParams`));
                    console.log('Stored Dish Param after setting recipes:', sessionStorage.getItem(`storedDishParam`));
                    console.log('Total results: ', data.totalResults);
                    console.log('Current page after setting the recipes', currentPage)

                } catch (error) {
                    console.error("Error fetching the recipes: ", error);
                }
            }            
        }

        fetchRecipes();
    }, [dishParam, ingredientParams, dietParams]);
    

    
    useEffect(() => {
        if (Array.isArray(recipes) && recipes.length > 0) {
            const savedScrollPosition = sessionStorage.getItem(`scrollPosition`);
            const savedCurrentRecipePage = sessionStorage.getItem(`currentRecipePage`);

            if (savedCurrentRecipePage){
                setCurrentPage(parseInt(savedCurrentRecipePage, 10));
                sessionStorage.removeItem("currentRecipePage");              
            }

            if (savedScrollPosition) {   
                window.scrollTo(0, parseInt(savedScrollPosition, 10));
                sessionStorage.removeItem("scrollPosition");                                         
            }
        } 
    }, [recipes]);

   /* useEffect(() => {
        if (!scrollRestored) {
            window.scrollTo({top: 0});
        }
        setScrollRestored(false);

    },[currentPage])*/


    const handlePageChange = (event, value) => {
        // vaihtuuko [recipes] uuden sivun latautuessa? Ei varmaankaan
        //sessionStorage.setItem("currentRecipePage", value);
        setCurrentPage(value);
        console.log('Current page after changing a page: ', currentPage);
    };

    // Tämä tallettaa tiedon, mihin asti oli scrollattu
    const handleRecipeClick = (recipeId) => {
        sessionStorage.setItem("scrollPosition", window.scrollY);
        sessionStorage.setItem("currentRecipePage", currentPage);
        navigate(`/recipedetails/${recipeId}`);   
    };

    const recipesPerPage = 20;
    const lastRecipe = currentPage * recipesPerPage;
    const firstRecipe = lastRecipe - recipesPerPage;
    const currentRecipes = Array.isArray(recipes) && recipes.length > 0 ? recipes.slice(firstRecipe, lastRecipe) : [];


    return (
        <Stack spacing={3} width="100%" sx={{alignItems: 'center'}}>
            
            {Array.isArray(recipes) && searched && recipes.length === 0 ? (
                
                <Card sx={{width: '80%', height: '250px'}}>
                    <CardContent
                      sx={{
                        display: 'flex',
                        flexDirection: 'column',
                        alignItems: 'center',
                        gap: 2,
                        padding: 2}}>
                        {responseOk ? (
                            <Typography>No recipes were found</Typography>
                        ) : (
                            <Typography>Unable to retrieve recipes at the moment</Typography>
                        )}
                    </CardContent>
                </Card>

            ) : (
                <>
                    {Array.isArray(recipes) && recipes.length > 0 && (
                        <>
                            <Typography variant="body2">Found {recipes.length} recipes</Typography>
                            
                            {currentRecipes.map((recipe, index) => (
                                <Card
                                    key={recipe.id}
                                    sx={{width: '80%', minHeight: '250px'}}
                                    onClick={() => handleRecipeClick(recipe.id)}>                
                                    <CardContent 
                                        sx={{
                                        display: 'flex',
                                        flexDirection: 'column',
                                        alignItems: 'center',
                                        gap: 2,
                                        padding: 2}}>
                                        
                                        <Typography>{recipe.title}</Typography>
                                        <img
                                            src={recipe.image}
                                            alt={recipe.title}
                                            style={{maxWidth: '100%', height:'auto', objectFit:'contain' }}
                                        />
                                        <Typography sx={{alignSelf: 'flex-end', paddingRight:2}} variant="body2">
                                            {index + 1} of {currentRecipes.length} on page {currentPage}
                                        </Typography>

                                    </CardContent>                   
                                </Card>
                            ))}
                            <Pagination
                                count={Math.ceil(recipes.length / recipesPerPage)}
                                color="primary"
                                size="large"
                                page={currentPage}
                                onChange={handlePageChange}
                             />
                            <Button variant="contained" onClick={() => {window.scrollTo({top: 0});}}>
                                Back to top
                            </Button>
                        </>
                    )}
                </>
            )}
        </Stack>
    );
}

export default RecipeList;