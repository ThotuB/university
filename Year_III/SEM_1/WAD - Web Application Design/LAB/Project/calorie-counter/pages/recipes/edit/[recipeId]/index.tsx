import axios from "axios";
import Loading from "components/common/Loading";
import Layout from "components/layouts/navigation/Layout";
import RecipeEditPage from "components/recipes/edit/RecipeEditPage";
import { GetServerSideProps } from "next";
import { useEffect, useState } from "react";
import { IRecipe } from "types/recipe";

interface Props {
    id: string;
}

export default function ({ id }: Props) {
    const [loading, setLoading] = useState(true);
    const [recipe, setRecipe] = useState<IRecipe>({} as IRecipe);

    useEffect(() => {
        const url = `http://localhost:3000/api/recipe/${id}`;

        axios.get(url)
            .then(res => {
                setRecipe(res.data);
                setLoading(false);
            })
    }, [])

    return (
        <Layout>
            {loading ?
                <Loading /> :
                <RecipeEditPage recipe={recipe} />
            }
        </Layout>
    );
}

export const getServerSideProps: GetServerSideProps = async (context) => {
    const { recipeId } = context.query;

    return {
        props: {
            id: recipeId as string
        }
    }
}