import Nutrients, { Nutrient } from 'components/food/[foodId]/Nutrients'
import Layout from 'components/layouts/navigation/Layout'
import axios from 'axios';
import { useState, useEffect } from 'react';
import { GetServerSideProps } from 'next';
import Loading from 'components/common/Loading';

interface Props {
    id: string;
    apiKey: string;
}

export default function Food({ id, apiKey }: Props) {
    const [loading, setLoading] = useState(true);
    const [food, setFood] = useState<Nutrient>({} as Nutrient);

    useEffect(() => {
        const url = `https://api.nal.usda.gov/fdc/v1/food/${id}`;
        const query = {
            params: {
                api_key: apiKey
            }
        }

        axios.get(url, query)
            .then(res => {
                setFood(res.data);
                setLoading(false);
            })
    }, [])

    return (
        <Layout>
            {loading ?
                <Loading /> :
                <Nutrients food={food} />
            }
        </Layout>
    );
}

export const getServerSideProps: GetServerSideProps = async (context) => {
    const id = context.query.foodId;
    const apiKey = process.env.USDA_API_KEY;

    return {
        props: {
            id: id,
            apiKey: apiKey
        }
    }
}