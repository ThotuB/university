import FoodList from 'components/food/Foods';
import Summary from 'components/common/goal/Summary';
import Loading from 'components/common/Loading';
import Pagination from 'components/common/Pagination';
import Layout from 'components/layouts/navigation/Layout';
import { useState, useEffect } from 'react';
import { GetServerSideProps } from 'next';
import axios from 'axios';

interface Props {
    apiKey: string;
    search: string;
}

export default function Index({ apiKey, search }: Props) {
    const [foods, setFoods] = useState([]);
    const [pages, setPages] = useState(0);
    const [page, setPage] = useState(1);
    const [total, setTotal] = useState(0);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        const url = `https://api.nal.usda.gov/fdc/v1/search`
        const query = {
            params: {
                api_key: apiKey,
                generalSearchInput: search,
                dataType: 'Branded',
                pageNumber: page,
                pageSize: 10,
            }
        }

        setLoading(true);
        axios.get(url, query)
            .then(res => {
                setFoods(res.data.foods);
                setPages(res.data.totalPages);
                setTotal(res.data.totalHits);
                setLoading(false);
            })
            .catch(err => {
                console.log(err);
            })
    }, [search, page]);

    return (
        <Layout>
            <div className="max-w-3xl w-full">
                <Summary goal={0} food={0} excercise={0} macros={{
                    protein: 0,
                    carbs: 0,
                    fat: 0
                }} />
            </div>
            {loading ? <Loading /> : <FoodList items={foods} />}
            <Pagination page={page} count={pages} onPageChange={setPage} />
        </Layout>
    );
}

export const getServerSideProps: GetServerSideProps = async (context) => {
    const apiKey = process.env.USDA_API_KEY;
    const search = context.query.search || '';

    return {
        props: {
            apiKey: apiKey,
            search: search
        }
    }
}