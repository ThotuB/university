import axios from 'axios';
import Loading from 'components/common/Loading';
import Pagination from 'components/common/Pagination';
import { useEffect, useState } from 'react';
import Recipes from './Recipes';

export default function FilteredRecipes() {
    const [recipes, setRecipes] = useState([])
    const [page, setPage] = useState(1)
    const [count, setCount] = useState(0)
    const [loading, setLoading] = useState(false)

    useEffect(() => {
        const url = `http://localhost:3000/api/recipes`
        const query = {
            params: {
                pageNumber: page,
                pageSize: 10
            }
        }

        setLoading(true)
        axios.get(url, query)
            .then(res => {
                setRecipes(res.data.recipes)
                setCount(res.data.pages)
                setLoading(false)
            })
            .catch(err => {
                console.log(err)
            })

    }, [page])

    return (
        <div className="flex flex-col gap-6 w-full items-center">
            <div className="w-full h-px bg-gray-800" />
            <div className="text-5xl font-bold font-futura-book">
                Popular Recipes
            </div>
            <div className="w-full h-px bg-gray-800" />
            {loading ? <Loading /> : <Recipes recipes={recipes} />}
            <Pagination count={count} page={page} onPageChange={setPage} />
        </div>
    )
}