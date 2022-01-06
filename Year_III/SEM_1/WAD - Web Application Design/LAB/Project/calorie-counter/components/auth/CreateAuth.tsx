import Button from 'components/common/Button'
import TextField from 'components/common/TextField'
import { Dispatch, SetStateAction, useState } from 'react'
import { EyeIcon, EyeOffIcon } from '@heroicons/react/outline'

type SetError = Dispatch<SetStateAction<Error>>

interface Error {
    error: boolean
    message: string
}

const defaultError = {
    error: false,
    message: ''
}

export default function CreateAuth() {
    const [username, setUsername] = useState('')
    const [email, setEmail] = useState('')
    const [password, setPassword] = useState('')
    const [confirmPassword, setConfirmPassword] = useState('')

    const [usernameError, setUsernameError] = useState<Error>(defaultError)
    const [emailError, setEmailError] = useState<Error>(defaultError)
    const [passwordError, setPasswordError] = useState<Error>(defaultError)
    const [confirmPasswordError, setConfirmPasswordError] = useState<Error>(defaultError)

    const [showPassword, setShowPassword] = useState(false)

    const validate = () => {
        let isValid = validateUsername(username, setUsernameError)
        isValid = validateEmail(email, setEmailError) && isValid
        isValid = validatePassword(password, setPasswordError) && isValid
        isValid = validateConfirmPassword(confirmPassword, password, setConfirmPasswordError) && isValid

        return isValid
    }

    const handleCreate = () => {
        if (!validate()) return
        console.log('Create user')
    }

    return (
        <form className="mt-6 flex flex-col gap-4"
            autoComplete="off"
            onSubmit={e => e.preventDefault()}
        >
            <TextField label='Username' type="text"
                value={username}
                onChange={(event) => setUsername(event.target.value)}
                maxLength={20}
                required
                error={usernameError.error}
                errorText={usernameError.message}
            />
            <TextField label='Email' type="text"
                value={email}
                onChange={(event) => setEmail(event.target.value)}
                maxLength={50}
                required
                error={emailError.error}
                errorText={emailError.message}
            />
            <div className='flex gap-2'>
                <TextField label='Password' type={showPassword ? 'text' : 'password'}
                    value={password}
                    onChange={(event) => setPassword(event.target.value)}
                    maxLength={20}
                    required
                    error={passwordError.error}
                    errorText={passwordError.message}
                />
                <button onClick={() => setShowPassword(!showPassword)}>
                    {showPassword ? <EyeIcon className="w-6 pt-7" /> : <EyeOffIcon className="w-6 pt-7" />}
                </button>
            </div>
            <TextField label='Confirm Password' type="password"
                value={confirmPassword}
                onChange={(event) => setConfirmPassword(event.target.value)}
                maxLength={20}
                required
                error={confirmPasswordError.error}
                errorText={confirmPasswordError.message}
            />

            <Button onClick={handleCreate}>
                Create Account
            </Button>
        </form>
    )
}

// Possible errors
const requiredError = (value: string, setError: SetError) => {
    if (value.length === 0) {
        setError({
            error: true,
            message: 'Required*'
        })
        return false
    }
    return true
}

const emailRegex = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/
const passwordRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,}$/
const invalidError = (value: string, regex: string | RegExp, setError: SetError) => {
    if (!value.match(regex)) {
        setError({
            error: true,
            message: 'Invalid'
        })
        return false
    }
    return true
}

const alreadyExistsError = (value: string, setError: SetError) => {
    // TODO: check if username or email already exists
    if (false) {
        setError({
            error: true,
            message: 'Already exists'
        })
        return false
    }
    return true
}

const passwordMatchError = (value: string, password: string, setError: SetError) => {
    if (value !== password) {
        setError({
            error: true,
            message: 'Passwords do not match'
        })
        return false
    }
    return true
}

// Validations
const validateUsername = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!alreadyExistsError(value, setError)) return false
    setError(defaultError)
    return true
}

const validateEmail = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!invalidError(value, emailRegex, setError)) return false
    if (!alreadyExistsError(value, setError)) return false
    setError(defaultError)
    return true
}

const validatePassword = (value: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!invalidError(value, passwordRegex, setError)) return false
    setError(defaultError)
    return true
}

const validateConfirmPassword = (value: string, password: string, setError: SetError) => {
    if (!requiredError(value, setError)) return false
    if (!passwordMatchError(value, password, setError)) return false
    setError(defaultError)
    return true
}