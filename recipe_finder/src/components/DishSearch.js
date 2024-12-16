import React from "react";
import {Autocomplete, TextField} from "@mui/material";


const DISH_LIST = [
    'Bruschetta',
    'French Fries',
    'Nachos',
    'Stroganoff',
    'Butter Chicken',
    'Tikka Masala',
    'Fish and Chips',
    'Sandwich',
    'Hamburger',
    'Lasagna',
    'Pad Thai',
    'Pizza',
    'Bolognese',
    'Carbonara',
    'Sushi',
    'Tacos',
    'Pie',
    'Brownies',
    'Cheesecake',
    'Cookies',
    'Creme Brulee',
    'Ice Cream',
    'Panna Cotta',
    'Tiramisu',
    'Cupcakes',
    'Beef Wellington',
    'Bouillabaisse',
    'Falafel',
    'Goulash',
    'Moussaka',
    'Paella',
    'Pho',
    'Poutine',
    'Ratatouille',
    'Ramen',
    'Samosa',
    'Noodle Soup',
    'Clam Chowder',
    'Minestrone',
    'Tom Yum',
    'Tortilla',
    'Antipasto',
    'Dip',
    'Salad',
    'Ceviche',
    'Cake',
    'Guacamole',
    'Hummus',
    'Meatballs',
    'Quesadillas',
    'Shrimp Cocktail',
    'Spring Rolls',
    'Beef Tenderloin',
    'Chili Con Carne',
    'Meatloaf',
    'Chicken Curry',
    'Enchiladas',
    'Fajitas',
    'Chicken Teriyaki',
    'BBQ Ribs',
    'Pork Chops',
    'Steak',
    'Stuffed Peppers',
    'Apple Crumble',
    'Banana Bread',
    'Muffins',
    'Pudding',
    'Carrot Cake',
    'Chocolate Fondue',
    'Cinnamon Rolls',
    'Fruit Tart',
    'Key Lime Pie',
    'Lemon Bars',
    'Pecan Pie',
    'Pumpkin Pie',
    'Red Velvet Cake',
    'Rice Pudding',
    'Strawberry Shortcake',
    'Trifle',
    'Bolognese Sauce',
    'Cannelloni',
    'Gnocchi',
    'Osso Buco',
    'Risotto',
    'Saltimbocca',
    'Burritos',
    'Chiles Rellenos',
    'Enchiladas',
    'Fajitas',
    'Tamales',
    'Biryani',
    'Chana Masala',
    'Dal Tadka',
    'Korma',
    'Palak Paneer',
    'Chow Mein',
    'Kung Pao Chicken',
    'Mapo Tofu',
    'Peking Duck',
    'Sweet and Sour Chicken',
    'Donburi',
    'Okonomiyaki',
    'Sashimi',
    'Tempura',
    'Udon',
    'Baba Ganoush',
    'Kebabs',
    'Shawarma',
    'Tabouleh',
    'Beef Stew',
    'Borscht',
    'Gumbo',
    'Jambalaya',
    'Miso Soup',
    'New England Clam Chowder',
    'Tomato Basil Soup',
    'BLT',,
];


/**
 * Dish search field for typing a dish name or selecting one from an autocompleted
 * list of AI generated options. Transfers the selected dish for SearchBar component.
 * @param {string} selectedDish - empty string that stores user's selection
 * @param {function} setSelectedDish - setter function for storing user's selection
 * @returns MUI Autocomplete component that holds dish options
 */
function DishSearch({selectedDish, setSelectedDish}) {

  const handleChange = (event, newValue) => {
    if (newValue === null || newValue === '') {
      setSelectedDish('');
    } else {
      setSelectedDish(typeof newValue === 'string' ? newValue : '');
    }
  };

  return (
      <Autocomplete
          freeSolo
          autoSelect
          options={DISH_LIST}
          value={selectedDish}
          onChange={(event, newValue) => handleChange(event, newValue)}
          renderInput={(params) => 
              <TextField
                {...params}
                label="Dish"
                style={{width:'80%'}}
                InputProps={{...params.InputProps, type: 'search'}}
                />}
          renderOption={(props, option) => (<li {...props} key={option}>{option}</li>)}
      />
  )
}

export default DishSearch;