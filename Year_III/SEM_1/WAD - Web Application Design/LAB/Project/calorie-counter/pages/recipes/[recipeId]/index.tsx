import axios from "axios";
import Loading from "components/common/Loading";
import Layout from "components/layouts/navigation/Layout";
import Recipe from "components/recipes/[recipeId]/Recipe";
import { GetServerSideProps } from "next";
import { useEffect, useState } from "react";
import { getRecipe } from "services/recipe";
import { RecipeDto } from "types/recipe";

interface Props {
    id: string;
}

export default ({ id }: Props) => {
    const [loading, setLoading] = useState(true);
    const [recipe, setRecipe] = useState<RecipeDto>({} as RecipeDto);

    useEffect(() => {
        getRecipe(id)
            .then(res => {
                setRecipe(res.data);
                setLoading(false);
            })
    }, [])

    return (
        <Layout>
            {loading ?
                <Loading /> :
                <Recipe recipe={recipe} />
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