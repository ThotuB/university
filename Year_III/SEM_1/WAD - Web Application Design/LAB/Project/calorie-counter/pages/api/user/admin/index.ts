import { MongoClient } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

export default async function handler(req: NextApiRequest, res: NextApiResponse) {
    if (req.method === 'POST') {
        const data = req.body;
        const { token } = req.query;

        if (token !== 'secret') {
            res.status(401).json({ message: 'Unauthorized' });
            return;
        }

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/users?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('admin');

        const result = await collection.insertOne(data)

        client.close()

        res.status(201).json({ message: 'Admin added', })
    }
}
