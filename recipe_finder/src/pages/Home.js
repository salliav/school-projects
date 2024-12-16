import React from 'react';
import {Container, Box} from '@mui/material';
import SearchBar from '../components/SearchBar';


/**
* Home page component holding the search bar. SearchBar renders
* the results after a search has been performed.
*/
function Home() {
    return (
        <Container disableGutters style={{width: '100%'}}>
            <Box>
                <SearchBar/>
            </Box>              
        </Container>
    );
}

export default Home;

